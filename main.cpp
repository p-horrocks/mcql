#include <iostream>
#include <QGuiApplication>
#include <QLocalServer>
#include <QLocalSocket>
#include <QQmlApplicationEngine>

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

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
