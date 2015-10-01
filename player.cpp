#include "player.h"

#include "serverlink.h"

Player::Player(const QString& name, ServerLink* server) :
    server_(server),
    name_(name)
{
    mode_ = server_->defaultGamemode();
}

void Player::updateMode(McqlUtil::GameMode mode)
{
    if(mode_ != mode)
    {
        mode_ = mode;
        emit modeChanged();
    }
}
