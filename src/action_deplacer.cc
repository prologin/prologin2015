#include "actions.hh"

int ActionDeplacer::check(const GameState* st) const
{
    // FIXME
    return 0;
}

void ActionDeplacer::handle_buffer(utils::Buffer& buf)
{
    buf.handle(dest_);
    buf.handle(player_id_);
}

void ActionDeplacer::apply_on(GameState* st) const
{
    // FIXME
}
