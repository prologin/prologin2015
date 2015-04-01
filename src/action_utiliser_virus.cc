// FIXME License notice

#include "action_utiliser_virus.hh"

ActionUtiliserVirus::ActionUtiliserVirus(int player_id)
    : player_id_(player_id)
{
}

ActionUtiliserVirus::ActionUtiliserVirus()
    : player_id_(FIXME)
{
}

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

uint32_t ActionUtiliserVirus::player_id() const
{
    return player_id_;
}

uint32_t ActionUtiliserVirus::id() const
{
    return ID_ACTION_UTILISER_VIRUS;
}

