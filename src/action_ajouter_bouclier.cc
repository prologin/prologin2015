#include "actions.hh"

int ActionAjouterBouclier::check(const GameState* st) const
{
    // Check action points
    if (st->action_points(player_id_) < COUT_BOUCLIER) return PA_INSUFFISANTS;

    // Check that the agent's current position is a portal
    int portal_here = st->map().portal_id_maybe(st->player_pos(player_id_));
    if (portal_here == -1) return AUCUN_PORTAIL;

    if (st->owner(portal_here) == -1) return PORTAIL_NEUTRE;
    if (st->owner(portal_here) != player_id_) return PORTAIL_ENNEMI;

    if (st->num_shields(portal_here) >= MAX_BOUCLIERS) return LIMITE_BOUCLIERS;

    return 0;
}

void ActionAjouterBouclier::apply_on(GameState* st) const
{
    // Consume action points
    st->decrement_action_points(player_id_, COUT_LIEN);

    int portal_here = st->map().portal_id_maybe(st->player_pos(player_id_));
    st->add_shield(portal_here);
}
