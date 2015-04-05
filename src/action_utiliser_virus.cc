#include "actions.hh"

int ActionUtiliserVirus::check(const GameState* st) const
{
    // FIXME
    return 0;
}

void ActionUtiliserVirus::handle_buffer(utils::Buffer& buf)
{
    buf.handle(player_id_);
}

void ActionUtiliserVirus::apply_on(GameState* st) const
{
    // FIXME
}
