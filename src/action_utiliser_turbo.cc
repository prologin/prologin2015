// FIXME License notice

#include "actions.hh"

ActionUtiliserTurbo::ActionUtiliserTurbo(int player_id)
    : player_id_(player_id)
{
}

ActionUtiliserTurbo::ActionUtiliserTurbo()
    : player_id_(-1)
{
}

int ActionUtiliserTurbo::check(const GameState* st) const
{
    CHECK_PA(COUT_TURBO);
    return OK;
}

void ActionUtiliserTurbo::handle_buffer(utils::Buffer& buf)
{
    buf.handle(player_id_);
}

void ActionUtiliserTurbo::apply_on(GameState* st) const
{
    st->increment_move_points(player_id, GAIN_TURBO);
}

uint32_t ActionUtiliserTurbo::player_id() const
{
    return player_id_;
}

uint32_t ActionUtiliserTurbo::id() const
{
    return ID_ACTION_UTILISER_TURBO;
}

