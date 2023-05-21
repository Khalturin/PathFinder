#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTextCodec>

#include "bfs.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QGuiApplication app(argc, argv);


    QQmlApplicationEngine engine;

    BFS bfs;
    //bfs.searchThree(pair<int,int>{1,1}, pair<int,int>{5,3});


    QQmlContext *context = engine.rootContext();

    context->setContextProperty("bfs", &bfs);


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
