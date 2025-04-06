#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "ball.h"
#include "pong.h"
#include "bat.h" 

#include <QDebug>
#include <QFile>


int main(int argc, char* argv[])
{
    #if defined(Q_OS_WIN) && QT_VERSION_CHECK(5, 6, 0) <= QT_VERSION && QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    #endif

    QGuiApplication app(argc, argv);

    qmlRegisterType<Ball>("Game", 1, 0, "Ball"); 
    qmlRegisterType<Pong>("Game", 1, 0, "Pong");
    qmlRegisterType<Bat>("Game", 1, 0, "Bat");

    qDebug() << "QRC file exists:" << QFile::exists(":/main.qml");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
