// FIXME License notice

#include "actions.hh"

#include <tuple>

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
    CHECK_PA(COUT_CAPTURE);
    CHECK_PORTAL_HERE();
    PROHIBIT_OWN_PORTAL(portal_here);
    PROHIBIT_ENEMY_PORTAL(portal_here);
    return OK;
}

void ActionCapturer::handle_buffer(utils::Buffer& buf)
{
    buf.handle(player_id_);
}

void ActionCapturer::apply_on(GameState* st) const
{
    CONSUME_PA(COUT_CAPTURE);
    PORTAL_HERE();
    st->capture(portal_here, player_id_);
}

uint32_t ActionCapturer::player_id() const
{
    return player_id_;
}

uint32_t ActionCapturer::id() const
{
    return ID_ACTION_CAPTURER;
}

