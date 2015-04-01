// FIXME License notice

#include "action_utiliser_turbo.hh"

ActionUtiliserTurbo::ActionUtiliserTurbo(int player_id)
    : player_id_(player_id)
{
}

ActionUtiliserTurbo::ActionUtiliserTurbo()
    : player_id_(FIXME)
{
}

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

uint32_t ActionUtiliserTurbo::player_id() const
{
    return player_id_;
}

uint32_t ActionUtiliserTurbo::id() const
{
    return ID_ACTION_UTILISER_TURBO;
}

