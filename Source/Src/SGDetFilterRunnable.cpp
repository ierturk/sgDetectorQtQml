#include "SSDNet.h"
#include "SGDetFilterRunnable.h"

#include <QDebug>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QQmlContext>
#include <QDateTime>
#include <QtGui/QPainter>
#include "SGDetFilter.h"


QImage qt_imageFromVideoFrame(const QVideoFrame& f);

SGDetFilterRunnable::SGDetFilterRunnable(SGDetFilter* parent) :
    m_Filter(parent),
    m_Orientation(0),
    m_Flip(0) {

    ssdNet = new SSDNet();
    ssdNet->init(
                "/home/ierturk/Work/REPOs/ssd/ssdIE/outputs/mobilenet_v2_ssd320_clk_trainval2019/jit_model_040000.pt"
                );
}

QVideoFrame SGDetFilterRunnable::run(
        QVideoFrame *input,
        const QVideoSurfaceFormat &surfaceFormat,
        RunFlags flags) {
    Q_UNUSED(flags)

    if (!input->isValid())
    {
        qWarning("Invalid input format");
        return *input;
    }

    /*
    static qint64 lastDraw = 0;

    if (QDateTime::currentDateTime().currentMSecsSinceEpoch() < lastDraw + 500) {
    }
    else if (QDateTime::currentDateTime().currentMSecsSinceEpoch() < lastDraw + 1000) {
        return *input;
    } else {
        lastDraw = QDateTime::currentDateTime().currentMSecsSinceEpoch();
    }
     */

    m_Orientation = m_Filter ? m_Filter->property("orientation").toInt() : 0;

#ifdef Q_OS_ANDROID
    m_Flip = true;
#else
    m_Flip = surfaceFormat.scanLineDirection() == QVideoSurfaceFormat::BottomToTop;
#endif

    QImage image = QVideoFrameToQImage(input);
    if (ssdNet->isInitialized() && image.isNull()) {
        return *input;
    }

    auto start = std::chrono::high_resolution_clock::now();

    ssdNet->setInput(image);
    ssdNet->forward();
    ssdNet->postProcess();
    image = ssdNet->getOut();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    // std::cout << "frame rate : " << 1000.0f / duration.count() << " fps" << '\n';



    if (image.format() != QImage::Format_ARGB32) {
        image = image.convertToFormat(QImage::Format_ARGB32);
    }

    // QPainter qPainter(&image);
    // QFontInfo font = qPainter.fontInfo();
    // qPainter.setFont(QFont(font.family(), 64));
    // qPainter.drawText(200,200,"sgDetector");

    // drawRedGreenPixels(image);

    return QVideoFrame(image);
}

QImage SGDetFilterRunnable::QVideoFrameToQImage(QVideoFrame* input) {

    switch (input->handleType()) {
        case QAbstractVideoBuffer::NoHandle:
            return QVideoFrameToQImage_using_Qt_internals(input);

        case QAbstractVideoBuffer::GLTextureHandle:
            return QVideoFrameToQImage_using_GLTextureHandle(input);

        case QAbstractVideoBuffer::XvShmImageHandle:
        case QAbstractVideoBuffer::CoreImageHandle:
        case QAbstractVideoBuffer::QPixmapHandle:
        case QAbstractVideoBuffer::EGLImageHandle:
        case QAbstractVideoBuffer::UserHandle:
            break;
    }

    return QImage();
}

QImage SGDetFilterRunnable::QVideoFrameToQImage_using_Qt_internals(QVideoFrame* input) {
    return qt_imageFromVideoFrame(*input);
}

QImage SGDetFilterRunnable::QVideoFrameToQImage_using_GLTextureHandle(QVideoFrame* input)
{
    QImage image(input->width(), input->height(), QImage::Format_ARGB32);
    GLuint textureId = static_cast<GLuint>(input->handle().toInt());
    QOpenGLContext* ctx = QOpenGLContext::currentContext();
    QOpenGLFunctions* f = ctx->functions();
    GLuint fbo;
    f->glGenFramebuffers(1, &fbo);
    GLint prevFbo;
    f->glGetIntegerv(GL_FRAMEBUFFER_BINDING, &prevFbo);
    f->glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    f->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId, 0);
    f->glReadPixels(0, 0, input->width(), input->height(), GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
    f->glBindFramebuffer(GL_FRAMEBUFFER, static_cast<GLuint>(prevFbo));
    return image;
}

void SGDetFilterRunnable::drawRedGreenPixels(QImage& image)
{
    auto bits = image.bits();
    int bytesPerLine = image.bytesPerLine();
    auto bytesPerPixel = bytesPerLine / image.width();
    for (int y = 0; y < image.height() && y < 32; y++)
    {
        unsigned char* line = bits + y * bytesPerLine;
        auto leftPixel = line;
        auto rightPixel = line + bytesPerLine - bytesPerPixel;
        for (int x = 0; x < image.width() && x < 32; x++)
        {
            leftPixel[0] = 0;
            leftPixel[1] = 255;
            leftPixel[2] = 0;
            leftPixel += bytesPerPixel;
            rightPixel[0] = 0;
            rightPixel[1] = 0;
            rightPixel[2] = 255;
            rightPixel -= bytesPerPixel;
        }
    }
}
