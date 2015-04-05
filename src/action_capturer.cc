#include "actions.hh"

int ActionCapturer::check(const GameState* st) const
{
    // FIXME
    return 0;
}

void ActionCapturer::handle_buffer(utils::Buffer& buf)
{
    buf.handle(player_id_);
}

void ActionCapturer::apply_on(GameState* st) const
{
    // FIXME
}
