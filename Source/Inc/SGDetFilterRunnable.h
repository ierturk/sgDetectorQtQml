#ifndef SGDETFILTERRUNNABLE_H
#define SGDETFILTERRUNNABLE_H

#include <QVideoFrame>
#include <QVideoFilterRunnable>

class SGDetFilter;
class SSDNet;
class SGDetFilterRunnable : public QVideoFilterRunnable {
public:
    SGDetFilterRunnable(SGDetFilter* parent = nullptr);

    QVideoFrame run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags) Q_DECL_OVERRIDE;

    static QImage QVideoFrameToQImage(QVideoFrame* input);
    static QImage QVideoFrameToQImage_using_Qt_internals(QVideoFrame* input);
    static QImage QVideoFrameToQImage_using_GLTextureHandle(QVideoFrame* input);
    static void drawRedGreenPixels(QImage& image);

protected:
    SGDetFilter* m_Filter;
    int m_Orientation;
    int m_Flip;
    SSDNet* ssdNet;
};

#endif // SGDETFILTERRUNNABLE_H
