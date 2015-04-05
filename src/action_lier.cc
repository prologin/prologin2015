#include "actions.hh"

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
