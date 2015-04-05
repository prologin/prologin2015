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
    // Check action points
    if (st->action_points(player_id_) < (COUT_VIRUS)) return PA_INSUFFISANTS;

    // Check that the agent's current position is a portal
    int portal_here = st->map().portal_id_maybe(st->player_pos(player_id_));
    if (portal_here == -1) return AUCUN_PORTAIL;

    if (st->owner(portal_here) == player_id_) return PORTAIL_NEUTRE;;

    return 0;
}

void ActionUtiliserVirus::handle_buffer(utils::Buffer& buf)
{
    buf.handle(player_id_);
}

void ActionUtiliserVirus::apply_on(GameState* st) const
{
    // Consume action points
    st->decrement_action_points(player_id_, COUT_VIRUS);

    int portal_here = st->map().portal_id_maybe(st->player_pos(player_id_));
    st->capture(portal_here, st->get_opponent(st->owner(portal_here)));
}

uint32_t ActionUtiliserVirus::player_id() const
{
    return player_id_;
}

uint32_t ActionUtiliserVirus::id() const
{
    return ID_ACTION_UTILISER_VIRUS;
}

