#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QSharedPointer>

#include "mcqlutil.h"
class ServerLink;

class Player :
        public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString            name READ name CONSTANT)
    Q_PROPERTY(McqlUtil::GameMode mode READ mode NOTIFY modeChanged)

public:
    Player(const QString& name, ServerLink* server);

    const QString& name() const { return name_; }

    McqlUtil::GameMode mode() const { return mode_; }
    void updateMode(McqlUtil::GameMode mode);

signals:
    void modeChanged();

protected:
    ServerLink* const server_;

    const QString      name_;
    McqlUtil::GameMode mode_;
};
typedef QSharedPointer<Player> PlayerPtr;

#endif // PLAYER_H
