#include "actions.hh"

#include <tuple>

int ActionCapturer::check(const GameState* st) const
{
    // Check action points
    if (st->action_points(player_id_) < (COUT_CAPTURE)) return PA_INSUFFISANTS;

    // Check that the agent's current position is a portal
    int portal_here = st->map().portal_id_maybe(st->player_pos(player_id_));
    if (portal_here == -1) return AUCUN_PORTAIL;

    if (st->owner(portal_here) == player_id_) return PORTAIL_AMI;;
    if (st->owner(portal_here) == player_id_) return PORTAIL_ENNEMI;;
    return OK;
}

void ActionCapturer::apply_on(GameState* st) const
{
    // Consume action points
    st->decrement_action_points(player_id_, COUT_CAPTURE);

    int portal_here = st->map().portal_id_maybe(st->player_pos(player_id_));
    st->capture(portal_here, player_id_);
}
