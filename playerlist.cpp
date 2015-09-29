#include "playerlist.h"

namespace
{

const int NAME_ROLE = Qt::UserRole;

} // namespace

PlayerList::PlayerList()
{
}

QHash<int, QByteArray> PlayerList::roleNames() const
{
    auto retval = QHash<int, QByteArray>();
    retval[NAME_ROLE] = "name";
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
    }
    return QVariant();
}

void PlayerList::addPlayer(const QString& name)
{
    beginInsertRows(QModelIndex(), players_.size(), players_.size());
    players_.push_back(QSharedPointer<Player>(new Player(name)));
    endInsertRows();
}
