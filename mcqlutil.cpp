#include "mcqlutil.h"

#include <cassert>
#include <QDebug>
#include <QDir>
#include <QTextStream>
#include <QUuid>

namespace
{

const char* PROP_TEMPLATE = R"(#Minecraft server properties
spawn-protection=16
max-tick-time=60000
offline-mode=true
generator-settings=
force-gamemode=false
allow-nether=true
broadcast-console-to-ops=true
enable-query=false
player-idle-timeout=0
spawn-monsters=true
op-permission-level=4
resource-pack-hash=
announce-player-achievements=false
snooper-enabled=true
level-type=DEFAULT
hardcore=false
enable-command-block=false
max-players=20
network-compression-threshold=256
max-world-size=29999984
server-port=25565
debug=true
server-ip=
spawn-npcs=true
allow-flight=false
level-name=world
view-distance=10
resource-pack=
spawn-animals=true
white-list=false
generate-structures=true
max-build-height=256
online-mode=false
level-seed=
use-native-transport=true
enable-rcon=false
motd=A MCQL World
)";

QString worldPath(const QString& name)
{
    return QDir::home().absoluteFilePath(QString(".mcql/%1").arg(name));
}

void copyDir(const QString& src, const QString& dst)
{
    if(!QDir().mkpath(dst))
        throw std::runtime_error("Unable to create directory " + dst.toStdString());

    auto srcDir = QDir(src);
    auto dstDir = QDir(dst);

    for(const auto& file : srcDir.entryList(QDir::Files | QDir::NoSymLinks | QDir::Readable))
    {
        auto s = srcDir.absoluteFilePath(file);
        auto d = dstDir.absoluteFilePath(file);
        if(!QFile::copy(s, d))
            throw std::runtime_error("Unable to copy " + s.toStdString() + " to " + d.toStdString());
    }

    for(const auto& dir : srcDir.entryList(QDir::Dirs | QDir::NoSymLinks | QDir::Readable | QDir::NoDotAndDotDot))
    {
        auto s = srcDir.absoluteFilePath(dir);
        auto d = dstDir.absoluteFilePath(dir);
        copyDir(s, d);
    }
}

} // namespace

void McqlUtil::initialiseWorld(const QString& name, int type, Difficulty difficulty, int hurting)
{
    auto path = worldPath(name);
    if(!QDir().mkpath(path))
    {
        emit creationError(tr("Unable to create world directory"));
        return;
    }

    QFile eula(path + "/eula.txt");
    if(!eula.open(QIODevice::WriteOnly))
    {
        emit creationError(tr("Unable to create eula.txt"));
        return;
    }
    eula.write("eula=true\n");

    QFile serverProperties(path + "/server.properties");
    if(!serverProperties.open(QIODevice::WriteOnly))
    {
        emit creationError(tr("Unable to create server.properties"));
        return;
    }
    QTextStream os(&serverProperties);

    int diff = 0;
    switch(difficulty)
    {
    case Peaceful:
        diff = 0; break;
    case Easy:
        diff = 1; break;
    case Normal:
        diff = 2; break;
    case Hard:
        diff = 3; break;
    }

    os << PROP_TEMPLATE;
    os << "gamemode=" << type << endl;
    os << "pvp=" << (hurting ? "false" : "true") << endl;
    os << "difficulty=" << diff << endl;
}

QStringList McqlUtil::importableWorlds()
{
    auto path    = QDir::home().absoluteFilePath(".minecraft/saves");
    auto filters = QDir::NoDotAndDotDot | QDir::Dirs | QDir::Readable;
    return QDir(path).entryList(filters);
}

void McqlUtil::importWorld(const QString& source, const QString& destination)
{
    auto srcPath = QDir::home().absoluteFilePath(QString(".minecraft/saves/%1").arg(source));
    auto dstPath = worldPath(destination) + "/world";

    try
    {
        copyDir(srcPath, dstPath);
    }
    catch(const std::exception& e)
    {
        emit creationError(QString::fromUtf8(e.what()));
    }
}

QStringList McqlUtil::availableWorlds()
{
    auto path    = QDir::home().absoluteFilePath(".mcql");
    auto filters = QDir::NoDotAndDotDot | QDir::Dirs | QDir::Readable;
    return QDir(path).entryList(filters);
}

QString McqlUtil::genWorldName(const QString& seed)
{
    auto retval = seed;
    if(seed.isEmpty())
    {
        retval = QUuid::createUuid().toString();
        retval.replace("{", "");
        retval.replace("}", "");
    }
    return retval;
}

void McqlUtil::logError(const QString& err)
{
    qCritical() << err;
}

McqlUtil::McqlUtil()
{
    bool ok = connect(this, &McqlUtil::creationError, this, &McqlUtil::logError);
    assert(ok);
}
