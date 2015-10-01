#include "serverlink.h"

#include <cassert>
#include <QDebug>
#include <QDir>

ServerLink::ServerLink()
{
    running_    = false;
    difficulty_ = McqlUtil::Normal;

    bool ok = connect(
                &serverProcess_, &QProcess::readyReadStandardOutput,
                this, &ServerLink::readProcessStdout
                );
    assert(ok);

    ok = connect(
                &serverProcess_, &QProcess::stateChanged,
                this, &ServerLink::onStateChange
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

void ServerLink::sendInput(const QString& input)
{
    auto data = input.toUtf8();
    data.append('\n');
    serverProcess_.write(data);
}

void ServerLink::stopServer()
{
    if(serverProcess_.state() != QProcess::NotRunning)
    {
        // Return immediately, we'll catch the signal when the server actually
        // stops.
        serverProcess_.write("stop\n");
    }
}

void ServerLink::readProcessStdout()
{
    auto data = serverProcess_.readAllStandardOutput();

    static const auto newPlayerRE  = QRegExp("\\[[^]]+\\]: ([^[]+)\\[[^]]+\\] logged in.*");
    static const auto lostPlayerRE = QRegExp("\\[[^]]+\\]: ([^ ]+) left the game.*");

    if(newPlayerRE.exactMatch(data))
    {
        playerList_.addPlayer(newPlayerRE.cap(1));
    }
    else if(lostPlayerRE.exactMatch(data))
    {
        playerList_.removePlayer(lostPlayerRE.cap(1));
    }
    else
    {
    }

    emit output(QString::fromUtf8(data));
}

void ServerLink::onStateChange(QProcess::ProcessState state)
{
    bool running = (state != QProcess::NotRunning);
    if(running != running_)
    {
        running_ = running;
        emit runningChanged();
    }
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

void ServerLink::readServerDefaults(const QString& dir)
{
    QFile serverProps(QDir(dir).absoluteFilePath("server.properties"));
    if(!serverProps.open(QIODevice::ReadOnly))
    {
        qCritical() << "Unable to open server.properties";
        return;
    }

    char lineData[2048];
    while(serverProps.readLine(lineData, sizeof(lineData)) >= 0)
    {
        auto line = QString::fromUtf8(lineData);

        // Trim comments.
        int pos = line.indexOf('#');
        if(pos >= 0)
        {
            line.truncate(pos);
        }
        line = line.trimmed();

        // Skip empty lines.
        if(line.isEmpty())
            continue;

        // Split into name/value pair.
        pos = line.indexOf('=');
        if(pos < 0)
            continue;

        auto name  = line.left(pos);
        auto value = line.mid(pos + 1);

    }
}
