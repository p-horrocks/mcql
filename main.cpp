#include <iostream>
#include <QGuiApplication>
#include <QLocalServer>
#include <QLocalSocket>
#include <QQmlApplicationEngine>
#include <qqml.h>

#include "mcqlutil.h"
#include "serverlink.h"

int main(int argc, char *argv[])
{
    const auto socketPath = QStringLiteral("/tmp/mcql.pipe");

    QLocalSocket singletonSocket;
    singletonSocket.connectToServer(socketPath);
    if(singletonSocket.waitForConnected(100))
    {
        std::cout << "Application instance is already running" << std::endl;
        return 0;
    }
    singletonSocket.disconnectFromServer();

    QLocalServer singletonServer;
    if(!singletonServer.listen(socketPath))
    {
        std::cerr << "Unable to open app singleton socket" << std::endl;
        return 1;
    }

    QGuiApplication app(argc, argv);

    const char* uri  = "app.mcql";
    const int verMaj = 1;
    const int verMin = 0;

    QQmlApplicationEngine engine;
    qmlRegisterSingletonType<McqlUtil>(uri, verMaj, verMin, "McqlUtil", &McqlUtil::qmlSingletonProvider);
    qmlRegisterType<ServerLink>(uri, verMaj, verMin, "ServerLink");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}
