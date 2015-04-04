// FIXME License notice

#include "actions.hh"

ActionAttaquer::ActionAttaquer(int energie, int player_id)
    : energie_(energie)
    , player_id_(player_id)
{
}

ActionAttaquer::ActionAttaquer()
    : energie_(-1)
    , player_id_(-1)
{
}

int ActionAttaquer::check(const GameState* st) const
{
    CHECK_POSITIVE(energie_); // à virer de toute façon
    // Check action points
    if (st->action_points(player_id_) < (energie_ * COUT_ATTAQUE))
        return PA_INSUFFISANTS;

    // Check that the agent's current position is a portal
    int portal_here = st->map()->portal_id_maybe(st->player_pos(player_id_));
    if (portal_here == -1) return AUCUN_PORTAIL;

    if (st->owner(portal_here) == player_id_) return PORTAIL_AMI;
    if (st->owner(portal_here) == player_id_) return PORTAIL_NEUTRE;
    return OK;
}

void ActionAttaquer::handle_buffer(utils::Buffer& buf)
{
    buf.handle(energie_);
    buf.handle(player_id_);
}

void ActionAttaquer::apply_on(GameState* st) const
{
    // Consume action points
    st->action_points(player_id_) -= energie_ * COUT_ATTAQUE;

    int portal_here = st->map()->portal_id_maybe(st->player_pos(player_id_));
    st->increment_energy(portal_here, -energie_);
    if (st->portal_energy(portal_here) < 0)
        st->neutralize(portal_here);
}

uint32_t ActionAttaquer::player_id() const
{
    return player_id_;
}

uint32_t ActionAttaquer::id() const
{
    return ID_ACTION_ATTAQUER;
}

