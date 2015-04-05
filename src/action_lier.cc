// FIXME License notice

#include <utility>

#include "actions.hh"
#include "geometry.hh"


ActionLier::ActionLier(position portail, int player_id)
    : portail_(portail)
    , player_id_(player_id)
{
}

ActionLier::ActionLier()
    : portail_({-1,-1})
    , player_id_(-1)
{
}

#define VERTEX(n,f) st->portal_pos(std::get<n>(f))

int ActionLier::check(const GameState* st) const
{
    // Check action points
    if (st->action_points(player_id_) < (COUT_LIEN)) return PA_INSUFFISANTS;

    // Check out of bounds
    if (portail_.x < 0 || portail_.y < 0 ||
        portail_.x >= TAILLE_TERRAIN || portail_.y >= TAILLE_TERRAIN)
        return POSITION_INVALIDE;

    // Check that the agent's current position is a portal
    int portal_here = st->map().portal_id_maybe(st->player_pos(player_id_));
    if (portal_here == -1) return AUCUN_PORTAIL;

    // Check that the given position is a portal
    int portal_there = st->map().portal_id_maybe(portail_);
    if (portal_there == -1) return AUCUN_PORTAIL;

    if (st->owner(portal_here) == player_id_) return PORTAIL_ENNEMI;
    if (st->owner(portal_here) == -1) return PORTAIL_NEUTRE;
    if (st->owner(portal_there) == player_id_) return PORTAIL_ENNEMI;
    if (st->owner(portal_there) == -1) return PORTAIL_NEUTRE;

    // TODO improve algorithmic efficiency

    auto player_pos = st->player_pos(player_id_);

    auto links = st->graph().edges();
    for (auto l : links)
    {
        if (segments_intersect(player_pos, portail_,
                               st->portal_pos(l.first),
                               st->portal_pos(l.second)))
            return LIEN_INTERSECTION;
    }
    
    // If a link intersects a field, either it crosses the boundary
    // or both is endpoints are in the field

    auto fields = st->graph().triangles();
    for (auto f : fields)
    {
        if (point_in_triangle(VERTEX(0,f), VERTEX(1,f), VERTEX(2,f),
                              player_pos))
            return LIEN_CHAMP;
    }

    return OK;
}

void ActionLier::handle_buffer(utils::Buffer& buf)
{
    buf.handle(portail_);
    buf.handle(player_id_);
}

void ActionLier::apply_on(GameState* st) const
{
    // Consume action points
    st->decrement_action_points(player_id_, COUT_LIEN);

    int portal_here = st->map().portal_id_maybe(st->player_pos(player_id_));
    int portal_there = st->map().portal_id_maybe(portail_);
    st->graph().add_edge(std::make_pair(portal_here, portal_there));
}

uint32_t ActionLier::player_id() const
{
    return player_id_;
}

uint32_t ActionLier::id() const
{
    return ID_ACTION_LIER;
}

