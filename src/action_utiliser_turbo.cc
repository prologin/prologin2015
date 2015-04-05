#include "actions.hh"

int ActionUtiliserTurbo::check(const GameState* st) const
{
    // FIXME
    return 0;
}

void ActionUtiliserTurbo::handle_buffer(utils::Buffer& buf)
{
    buf.handle(player_id_);
}

void ActionUtiliserTurbo::apply_on(GameState* st) const
{
    // FIXME
}
