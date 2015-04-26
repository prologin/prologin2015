#include <utility>

#include "actions.hh"
#include "geometry.hh"
#include "errors.hh"

// TODO replace this macro with unpack_triangle_pos
#define VERTEX(n,f) st->portal_pos(std::get<n>(f))

int ActionLier::check(const GameState* st) const
{
    // Check action points
    if (st->action_points(player_id_) < COUT_LIEN) return PA_INSUFFISANTS;

    // Check out of bounds
    try {

    // Check that the given position is a portal
    // (raises an exception if OOB)
    int portal_there = st->map().portal_id_maybe(portail_);
    if (portal_there == -1) return AUCUN_PORTAIL;

    // Check that the agent's current position is a portal
    int portal_here = st->map().portal_id_maybe(st->player_pos(player_id_));
    if (portal_here == -1) return AUCUN_PORTAIL;

    // Check that the two portals are distinct
    if (portal_here == portal_there) return LIEN_DEGENERE;

    if (st->owner(portal_here) == -1) return PORTAIL_NEUTRE;
    if (st->owner(portal_here) == st->get_opponent(player_id_))
        return PORTAIL_ENNEMI;
    if (st->owner(portal_there) == -1) return PORTAIL_NEUTRE;
    if (st->owner(portal_there) == st->get_opponent(player_id_))
        return PORTAIL_ENNEMI;

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
    // or *both* its endpoints are in the field.
    // Therefore, we only have to check *one* of the endpoints:
    // the omission of the other one is not an error.

    auto fields = st->graph().triangles();
    for (auto f : fields)
    {
        if (point_in_triangle(VERTEX(0,f), VERTEX(1,f), VERTEX(2,f),
                              player_pos))
            return LIEN_CHAMP;
    }
    }
    catch (const InvalidPosition& exc)
    {
        return POSITION_INVALIDE;
    }

    return OK;
}

void ActionLier::apply_on(GameState* st) const
{
    // Consume action points
    st->decrement_action_points(player_id_, COUT_LIEN);

    // Score reward (TODO add test)
    st->increment_score(player_id_, POINTS_CREATION_LIEN);

    int portal_here = st->map().portal_id_maybe(st->player_pos(player_id_));
    int portal_there = st->map().portal_id_maybe(portail_);
    st->graph().add_edge(std::make_pair(portal_here, portal_there));
}
