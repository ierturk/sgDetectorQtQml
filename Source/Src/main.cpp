#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "SGDetFilter.h"

// #include <QQmlDebuggingEnabler>

int main(int argc, char *argv[])
{
    // QQmlDebuggingEnabler enabler;

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<SGDetFilter>("SGDetFilterLib", 1, 0, "SGDetFilter");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
