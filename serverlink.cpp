#include "serverlink.h"

#include <cassert>
#include <QDebug>
#include <QDir>
#include <QMetaEnum>

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

void ServerLink::setDifficulty(McqlUtil::Difficulty d)
{
    if(!running_ || (d == difficulty_))
        return;

    // Wait for the server to respond to change our value.
    sendInput(QString("difficulty %1").arg(static_cast<int>(d)));
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
        sendInput("stop");
    }
}

void ServerLink::readProcessStdout()
{
    auto data = QString::fromUtf8(serverProcess_.readAllStandardOutput());

    auto lines = data.split('\n');
    for(const auto& line : lines)
    {
        readStdoutLine(line);
    }

    emit output(data);
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

void ServerLink::_setDifficulty(McqlUtil::Difficulty d)
{
    if(d != difficulty_)
    {
        difficulty_ = d;
        emit difficultyChanged();
    }
}

void ServerLink::startServer()
{
    auto worldPath  = QDir::home().absoluteFilePath(QString(".mcql/%1").arg(worldName_));
    auto spigotPath = QDir::home().absoluteFilePath(".mcql/spigot-1.8.8.jar");

    readServerDefaults(worldPath);

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

        if(name == "difficulty")
        {
            _setDifficulty(static_cast<McqlUtil::Difficulty>(value.toInt()));
        }
    }
}

void ServerLink::readStdoutLine(const QString& line)
{
    static const auto newPlayerRE  = QRegExp("\\[[^]]+\\]: ([^[]+)\\[[^]]+\\] logged in.*");
    static const auto lostPlayerRE = QRegExp("\\[[^]]+\\]: ([^ ]+) left the game.*");
    static const auto difficultyRE = QRegExp("\\[[^]]+\\]: Set game difficulty to ([^ ]+).*");

    if(newPlayerRE.exactMatch(line))
    {
        playerList_.addPlayer(newPlayerRE.cap(1));
    }
    else if(lostPlayerRE.exactMatch(line))
    {
        playerList_.removePlayer(lostPlayerRE.cap(1));
    }
    else if(difficultyRE.exactMatch(line))
    {
        auto str  = difficultyRE.cap(1);
        auto type = QMetaEnum::fromType<McqlUtil::Difficulty>();
        auto d    = type.keyToValue(str.toUtf8());
        if(d >= 0)
        {
            _setDifficulty(static_cast<McqlUtil::Difficulty>(d));
        }
    }
    else
    {
    }
}
