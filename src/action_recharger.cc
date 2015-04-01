// FIXME License notice

#include "actions.hh"

ActionRecharger::ActionRecharger(position portail, int player_id)
    : portail_(portail)
    , player_id_(player_id)
{
}

ActionRecharger::ActionRecharger()
    : portail_({-1,-1})
    , player_id_(-1)
{
}

int ActionRecharger::check(const GameState* st) const
{
    // FIXME
    return 0;
}

void ActionRecharger::handle_buffer(utils::Buffer& buf)
{
    buf.handle(portail_);
    buf.handle(player_id_);
}

void ActionRecharger::apply_on(GameState* st) const
{
    // FIXME
}

uint32_t ActionRecharger::player_id() const
{
    return player_id_;
}

uint32_t ActionRecharger::id() const
{
    return ID_ACTION_RECHARGER;
}

