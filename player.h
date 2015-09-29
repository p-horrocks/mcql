#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QSharedPointer>

class Player :
        public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)

public:
    Player(const QString& name);

    const QString& name() const { return name_; }

protected:
    const QString name_;
};
typedef QSharedPointer<Player> PlayerPtr;

#endif // PLAYER_H
