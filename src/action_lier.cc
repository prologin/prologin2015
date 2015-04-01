// FIXME License notice

#include "action_lier.hh"

ActionLier::ActionLier(position portail, int player_id)
    : portail_(portail)
    , player_id_(player_id)
{
}

ActionLier::ActionLier()
    : portail_(FIXME)
    , player_id_(FIXME)
{
}

int ActionLier::check(const GameState* st) const
{
    // FIXME
    return 0;
}

void ActionLier::handle_buffer(utils::Buffer& buf)
{
    buf.handle(portail_);
    buf.handle(player_id_);
}

void ActionLier::apply_on(GameState* st) const
{
    // FIXME
}

uint32_t ActionLier::player_id() const
{
    return player_id_;
}

uint32_t ActionLier::id() const
{
    return ID_ACTION_LIER;
}

