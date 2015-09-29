#ifndef PLAYERLIST_H
#define PLAYERLIST_H

#include <QAbstractListModel>

#include "player.h"

class PlayerList :
        public QAbstractListModel
{
public:
    PlayerList();

    virtual QHash<int, QByteArray> roleNames() const;
    virtual int rowCount(const QModelIndex&) const;
    virtual QVariant data(const QModelIndex& index, int role) const;

    void addPlayer(const QString& name);
    void removePlayer(const QString& name);

protected:
    QList<PlayerPtr> players_;
};

Q_DECLARE_METATYPE(PlayerList*)

#endif // PLAYERLIST_H
