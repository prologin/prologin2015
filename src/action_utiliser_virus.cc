// FIXME License notice

#include "actions.hh"

ActionUtiliserVirus::ActionUtiliserVirus(int player_id)
    : player_id_(player_id)
{
}

ActionUtiliserVirus::ActionUtiliserVirus()
    : player_id_(-1)
{
}

int ActionUtiliserVirus::check(const GameState* st) const
{
    CHECK_PA(COUT_VIRUS);
    CHECK_PORTAL_HERE();
    PROHIBIT_NEUTRAL_PORTAL(OWN_PORTAL);
    return 0;
}

void ActionUtiliserVirus::handle_buffer(utils::Buffer& buf)
{
    buf.handle(player_id_);
}

void ActionUtiliserVirus::apply_on(GameState* st) const
{
    CONSUME_PA(COUT_VIRUS);
    PORTAL_HERE();
    capture(portal_here, st->get_opponent(st->owner(portal_here)));
}

uint32_t ActionUtiliserVirus::player_id() const
{
    return player_id_;
}

uint32_t ActionUtiliserVirus::id() const
{
    return ID_ACTION_UTILISER_VIRUS;
}

