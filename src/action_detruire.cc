#include "actions.hh"

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
