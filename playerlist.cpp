#include "playerlist.h"

namespace
{

const int NAME_ROLE = Qt::UserRole + 1;
const int MODE_ROLE = Qt::UserRole + 2;

} // namespace

PlayerList::PlayerList()
{
}

QHash<int, QByteArray> PlayerList::roleNames() const
{
    auto retval = QHash<int, QByteArray>();
    retval[NAME_ROLE] = "name";
    retval[MODE_ROLE] = "mode";
    return retval;
}

int PlayerList::rowCount(const QModelIndex&) const
{
    return players_.size();
}

QVariant PlayerList::data(const QModelIndex& index, int role) const
{
    if(index.parent().isValid() || (index.column() != 0))
        return QVariant();

    int row = index.row();
    if((row < 0) || (row >= players_.size()))
        return QVariant();

    const auto player = players_[row];
    switch(role)
    {
    case NAME_ROLE:
        return player->name();
    case MODE_ROLE:
        return player->mode();
    }
    return QVariant();
}

void PlayerList::addPlayer(const QString& name, ServerLink* server)
{
    beginInsertRows(QModelIndex(), players_.size(), players_.size());
    players_.push_back(QSharedPointer<Player>(new Player(name, server)));
    endInsertRows();
}

void PlayerList::removePlayer(const QString& name)
{
    for(int i = 0; i < players_.size(); ++i)
    {
        if(players_[i]->name() != name)
            continue;

        beginRemoveRows(QModelIndex(), i, i);
        players_.removeAt(i);
        endRemoveRows();
        break;
    }
}
