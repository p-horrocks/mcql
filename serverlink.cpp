#include "serverlink.h"

#include <cassert>
#include <QDir>

ServerLink::ServerLink()
{
    bool ok = connect(
                &serverProcess_, &QProcess::readyReadStandardOutput,
                this, &ServerLink::readProcessStdout
                );
    assert(ok);
}

void ServerLink::setWorldName(const QString& name)
{
    if(name != worldName_)
    {
        worldName_ = name;
        emit worldNameChanged();

        startServer();
    }
}

void ServerLink::readProcessStdout()
{
    auto data = serverProcess_.readAllStandardOutput();
    emit output(QString::fromUtf8(data));
}

void ServerLink::startServer()
{
    auto worldPath  = QDir::home().absoluteFilePath(QString(".mcql/%1").arg(worldName_));
    auto spigotPath = QDir::home().absoluteFilePath(".mcql/spigot-1.8.8.jar");

    auto args = QStringList();
    args << "-Xms1024M"<< "-Xmx1024M" << "-XX:MaxPermSize=128M";
    args << "-jar" << spigotPath;

    serverProcess_.setWorkingDirectory(worldPath);
    serverProcess_.start("java", args);
}
