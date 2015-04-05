#include "actions.hh"

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

void ActionUtiliserVirus::apply_on(GameState* st) const
{
    // Consume action points
    st->decrement_action_points(player_id_, COUT_VIRUS);

    int portal_here = st->map().portal_id_maybe(st->player_pos(player_id_));
    st->capture(portal_here, st->get_opponent(st->owner(portal_here)));
}
