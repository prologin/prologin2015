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
    CHECK_POSITIVE(energie_);
    CHECK_PA(energie_ * COUT_ATTAQUE);
    CHECK_PORTAL_HERE();
    PROHIBIT_OWN_PORTAL(portal_here);
    PROHIBIT_NEUTRAL_PORTAL(portal_here);
    return OK;
}

void ActionAttaquer::handle_buffer(utils::Buffer& buf)
{
    buf.handle(energie_);
    buf.handle(player_id_);
}

void ActionAttaquer::apply_on(GameState* st) const
{
    CONSUME_PA(energie_ * COUT_ATTAQUE);
    PORTAL_HERE();
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

