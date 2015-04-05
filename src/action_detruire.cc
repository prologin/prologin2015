// FIXME License notice

#include "actions.hh"

ActionDetruire::ActionDetruire(int player_id)
    : player_id_(player_id)
{
}

ActionDetruire::ActionDetruire()
    : player_id_(-1)
{
}

int ActionDetruire::check(const GameState* st) const
{
    // FIXME
    return 0;
}

void ActionDetruire::handle_buffer(utils::Buffer& buf)
{
    buf.handle(player_id_);
}

void ActionDetruire::apply_on(GameState* st) const
{
    // FIXME
}

uint32_t ActionDetruire::player_id() const
{
    return player_id_;
}

uint32_t ActionDetruire::id() const
{
    return ID_ACTION_DETRUIRE;
}

