#include "actions.hh"

int ActionNeutraliser::check(const GameState& st) const
{
    // Check that the agent's current position is a portal
    int portal_here = st.map().portal_id_maybe(st.player_pos(player_id_));
    if (portal_here == -1)
        return AUCUN_PORTAIL;

    // Check action points
    int n = st.num_shields(portal_here);
    int cost = COUT_NEUTRALISATION + n * COUT_NEUTRALISATION_BOUCLIER;
    if (st.action_points(player_id_) < cost)
        return PA_INSUFFISANTS;

    if (st.owner(portal_here) == player_id_)
        return PORTAIL_AMI;
    if (st.owner(portal_here) == -1)
        return PORTAIL_NEUTRE;

    return OK;
}

void ActionNeutraliser::apply_on(GameState* st) const
{
    int portal_here = st->map().portal_id_maybe(st->player_pos(player_id_));

    // Consume action points
    int n = st->num_shields(portal_here);
    int cost = COUT_NEUTRALISATION + n * COUT_NEUTRALISATION_BOUCLIER;
    st->decrement_action_points(player_id_, cost);

    st->neutralize(portal_here);
}
