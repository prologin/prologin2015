// FIXME License notice

#include "actions.hh"

ActionCapturer::ActionCapturer(int player_id)
    : player_id_(player_id)
{
}

ActionCapturer::ActionCapturer()
    : player_id_(-1)
{
}

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

uint32_t ActionCapturer::player_id() const
{
    return player_id_;
}

uint32_t ActionCapturer::id() const
{
    return ID_ACTION_CAPTURER;
}

