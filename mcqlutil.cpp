#include "mcqlutil.h"

#include <QDir>
#include <QTextStream>

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

} // namespace

void McqlUtil::initialiseWorld(const QString& name, int type, int difficulty, int hurting)
{
    auto path = QDir::home().absoluteFilePath(QString(".mcql/%1").arg(name));
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

    os << PROP_TEMPLATE;
    os << "gamemode=" << type << endl;
    os << "pvp=" << (hurting ? "false" : "true") << endl;
    os << "difficulty=" << difficulty << endl;
}
