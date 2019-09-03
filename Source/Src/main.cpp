#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>

// #include <QLoggingCategory>
// #include <QQmlDebuggingEnabler>

// #include <QMediaPlayer>
// #include <QMediaRecorder>
// #include <QQmlContext>

#include "SGDetFilter.h"


int main(int argc, char *argv[])
{
    /*
    QQmlDebuggingEnabler enabler;
    QLoggingCategory::setFilterRules(
                "*.debug=true\n"
                "qt.*.debug=false"
                );
    */

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<SGDetFilter>("SGDetFilterLib", 1, 0, "SGDetFilter");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
/*
    QObject *item = dynamic_cast<QObject *>(engine.rootObjects().at(0));
    QObject *m_player = item->findChild<QObject*>("video_cam00");
    QMediaPlayer *player = qvariant_cast<QMediaPlayer *>(m_player->property("mediaObject"));
    QMediaRecorder *recorder = new QMediaRecorder(player);
    QVideoEncoderSettings settings = recorder->videoSettings();
    settings.setResolution(640,480);
    settings.setQuality(QMultimedia::VeryHighQuality);
    settings.setFrameRate(30.0);
    settings.setCodec("video/mp4");
    recorder->setVideoSettings(settings);
    recorder->setContainerFormat("mp4");
    recorder->setOutputLocation(QUrl::fromLocalFile("/home/ierturk/media.mp4"));
    engine.rootContext()->setContextProperty("myRecorder", recorder);
    recorder->record();

    qDebug() << m_player->property("source");
*/
    return app.exec();
}
