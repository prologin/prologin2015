#include "actions.hh"

#include <tuple>

int ActionCapturer::check(const GameState& st) const
{
    // Check action points
    if (st.action_points(player_id_) < COUT_CAPTURE)
        return PA_INSUFFISANTS;

    // Check that the agent's current position is a portal
    int portal_here = st.map().portal_id_maybe(st.player_pos(player_id_));
    if (portal_here == -1)
        return AUCUN_PORTAIL;

    // It isn't allowed to seize a portal that already belongs to someone:
    // players have to "destroy" it first (see ActionDetruire).
    if (st.owner(portal_here) == -1)
        return OK;
    else if (st.owner(portal_here) == player_id_)
        return PORTAIL_AMI;
    else
        return PORTAIL_ENNEMI;
}

void ActionCapturer::apply_on(GameState* st) const
{
    // Consume action points
    st->decrement_action_points(player_id_, COUT_CAPTURE);

    // Score reward
    st->increment_score(player_id_, POINTS_CAPTURE);

    int portal_here = st->map().portal_id_maybe(st->player_pos(player_id_));
    st->capture(portal_here, player_id_);
}
