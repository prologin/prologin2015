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
    CHECK_PA(COUT_LIEN);
    CHECK_POSITION(portail_);
    CHECK_PORTAL_HERE();
    CHECK_PORTAL_THERE(portail_);
    PROHIBIT_ENEMY_PORTAL(portal_here);
    PROHIBIT_NEUTRAL_PORTAL(portal_here);
    PROHIBIT_ENEMY_PORTAL(portal_there);
    PROHIBIT_NEUTRAL_PORTAL(portal_there);

    // TODO improve algorithmic efficiency

    auto player_pos = st->position(player_id_);

    auto links = st->graph().edges();
    for (auto l : links)
    {
        if (segments_intersect(player_pos, portail_,
                               st->portal_pos(e.first),
                               st->portal_pos(e.second)))
            return LIEN_INTERSECTION;
    }
    
    // If a link intersects a field, either it crosses the boundary
    // or both is endpoints are in the field

    auto fields = st->graph().triangles();
    for (auto f : fields)
    {
        if (point_in_triangle(VERTEX(0,f), VERTEX(1,f), VERTEX(2,f),
                              player_pos)
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
    CONSUME_PA(COUT_LIEN);
    PORTAL_HERE();
    PORTAL_THERE(portail_);
    st->graph()->add_edge(std::make_pair(portal_here, portal_there));
}

uint32_t ActionLier::player_id() const
{
    return player_id_;
}

uint32_t ActionLier::id() const
{
    return ID_ACTION_LIER;
}

