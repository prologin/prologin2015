#include <utility>

#include "actions.hh"
#include "errors.hh"
#include "geometry.hh"

int ActionLier::check(const GameState& st) const
{
    // Check action points
    if (st.action_points(player_id_) < COUT_LIEN)
        return PA_INSUFFISANTS;

    // Check out of bounds
    try
    {

        // Check that the given position is a portal
        // (raises an exception if OOB)
        int portal_there = st.map().portal_id_maybe(portail_);
        if (portal_there == -1)
            return AUCUN_PORTAIL;

        // Check that the agent's current position is a portal
        position player_pos = st.player_pos(player_id_);
        int portal_here = st.map().portal_id_maybe(player_pos);
        if (portal_here == -1)
            return AUCUN_PORTAIL;

        // Check that the two portals are distinct
        if (portal_here == portal_there)
            return LIEN_DEGENERE;

        // Check that the player trying to create the link
        // controls both portals
        int opp_id = st.get_opponent(player_id_);
        if (st.owner(portal_here) == -1)
            return PORTAIL_NEUTRE;
        if (st.owner(portal_here) == opp_id)
            return PORTAIL_ENNEMI;
        if (st.owner(portal_there) == -1)
            return PORTAIL_NEUTRE;
        if (st.owner(portal_there) == opp_id)
            return PORTAIL_ENNEMI;

        // TODO improve algorithmic efficiency

        auto links = st.graph().edges();
        for (auto l : links)
        {
            if (segments_intersect(player_pos, portail_, st.portal_pos(l.first),
                                   st.portal_pos(l.second)))
                return LIEN_INTERSECTION;
        }

        // If a link intersects a field, either it crosses the boundary
        // or *both* its endpoints are in the field.
        // Therefore, we only have to check *one* of the endpoints:
        // the omission of the other one is not an error.

        auto fields = st.graph().triangles();
        for (auto& f : fields)
        {
            position a, b, c;
            st.unpack_triangle_pos(f, a, b, c);

            if (point_in_triangle(a, b, c, player_pos) ||
                point_in_triangle(a, b, c, portail_))
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

    int portal_here = st->map().portal_id_maybe(st->player_pos(player_id_));
    int portal_there = st->map().portal_id_maybe(portail_);
    st->graph().add_edge(std::make_pair(portal_here, portal_there));
}
