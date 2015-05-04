// FIXME License notice

#include <stdexcept>

#include "game_state.hh"
#include "constant.hh"
#include "geometry.hh"
#include "errors.hh"

GameState::GameState(std::istream& map_stream, rules::Players_sptr players)
    : rules::GameState()
    , players_(players)
    , current_round_(0)
    , map_(new Map(map_stream))
    // it's ok, map_ appears before all these variables in the .hh,
    // and is therefore initialized first
    , graph_(map_->num_portals())
    , portal_player_(map_->num_portals(), -1)
    , portal_shields_(map_->num_portals(), 0)
    , history_(new history_info)
{
    int player_ordinal = 0;
    for (auto& p : players_->players)
    {
        if (player_ordinal > 2)
            FATAL("This game cannot accomodate more than two players.");
        if (p->type == rules::PLAYER)
        {
            p->score = 0;
            player_info_[p->id] = (player_info) {
                .action_points = NB_POINTS_ACTION,
                .move_points = NB_POINTS_DEPLACEMENT,
                .pos = map_->get_start_position(player_ordinal),
                .score = &(p->score)
            };
            player_ordinal++;
        }
    }
}

GameState::GameState(const GameState& st)
    : rules::GameState(st)
    , players_(st.players_)
    , current_round_(st.current_round_)
    , map_(st.map_)
    , graph_(st.graph_)
    , portal_player_(st.portal_player_)
    , portal_shields_(st.portal_shields_)
    , player_info_(st.player_info_)
    , history_(st.history_)
{
    // I think that's the default copy constructor?
    // CHECK : can we remove this declaration?
}


GameState::~GameState()
{
}

rules::GameState* GameState::copy() const
{
    return new GameState(*this);
}

int GameState::get_current_round() const
{
    return current_round_;
}

void GameState::go_next_round()
{
    ++current_round_;
}

void GameState::reset_points(int player_id)
{
    // Check that the player_id refers to an actual player
    auto iter = player_info_.find(player_id);
    assert(iter != player_info_.end()); // should never happen

    player_info& pi = iter->second;

    // Reset points
    pi.action_points = NB_POINTS_ACTION;
    pi.move_points = NB_POINTS_DEPLACEMENT;
}

void GameState::end_of_player_turn(int player_id)
{
    // Check that the player_id refers to an actual player
    assert(player_info_.find(player_id) != player_info_.end());

    // Compute stuff
    auto edges = graph_.edges();
    auto triangles = graph_.triangles();

    // Update score with area covered by fields
    int area_x2 = 0;
    for (auto& t : triangles)
    {
        if (owner(t) == player_id)
            area_x2 += field_area_x2(t);
    }
    increment_score(player_id, (POINTS_CHAMP/2) * area_x2);

    // The rest of the function updates the history
    history_.reset(new history_info);
    rules::GameState *st = this;
    while (st->can_cancel())
    {
        // Retrieve the game state at the start of the turn
        // as the last element of the stack
        st = st->get_old_version();
    }
    GameState *old = dynamic_cast<GameState*>(st);
    int opponent = get_opponent(player_id);

    // Portals diff
    for (int i = 0; i < map_->num_portals(); ++i)
    {
        if (portal_player_[i] == player_id &&
            old->portal_player_[i] != player_id)
        {
            history_->hist_captured.push_back(portal_pos(i));
        }
        // TODO: precise in the yaml comment that using the virus to
        // neutralize one's own portal doesn't count towards this
        // something like "the portals that have stopped belonging
        // to you during your opponent's previous turn"
        if (portal_player_[i] != opponent &&
            old->portal_player_[i] == opponent)
        {
            history_->hist_neutralised.push_back(portal_pos(i));
        }
        // Shields, counting multiplicity
        for (int j = 0; j < portal_shields_[i] - old->portal_shields_[i]; ++j)
        {
            history_->hist_shields.push_back(portal_pos(i));
        }
    }

    // Links diff
    for (auto& e : edges)
    {
        // A new link is either a new edge on the graph, or
        // an opponent's link that was destroyed and replaced
        // by the current player
        if (!old->graph_.edge_exists(e) || old->owner(e) != owner(e))
            history_->hist_links.push_back(edge_to_link(e));
    }

    // Fields diff
    // Reuse the vector of triangles computed before
    for (const itriple& t : triangles)
    {
        // for once this doesn't use unpack_triangle_pos
        int v0 = std::get<0>(t);
        int v1 = std::get<1>(t);
        int v2 = std::get<2>(t);
        // A field is new if one of its links is new,
        // or its owner has changed
        if (!old->graph_.edge_exists({v0,v1}) ||
            !old->graph_.edge_exists({v1,v2}) ||
            !old->graph_.edge_exists({v2,v0}) ||
            old->owner(t) != owner(t))
            history_->hist_fields.push_back(triangle_to_field(t));
    }
}

bool GameState::is_finished() const
{
    return current_round_ > NB_TOURS;
}

int GameState::get_opponent(int player_id) const
{
    for (auto& pair : player_info_)
        if (pair.first != player_id)
            return pair.first;
    return -1;
}

int GameState::get_score(int player_id) const
{
    return *(player_info_.at(player_id).score);
}

void GameState::increment_score(int player_id, int delta)
{
    *(player_info_.at(player_id).score) += delta;
}

int GameState::owner(int portal_id) const
{
    return portal_player_[portal_id];
}

void GameState::neutralize(int portal_id)
{
    capture(portal_id, -1);
}

void GameState::capture(int portal_id, int player_id)
{
    portal_player_[portal_id] = player_id;
    // Don't forget to reset shields and remove incident links!
    portal_shields_[portal_id] = 0;
    graph_.remove_incident_edges(portal_id);
}

int GameState::owner(const ipair& link) const
{
    // TODO check that the two endpoints have the same owner
    // and raise error if the invariant is broken
    return owner(link.first);
}

int GameState::owner(const itriple& field) const
{
    return owner(std::get<0>(field));
}

lien GameState::edge_to_link(const ipair& e) const
{
    return (lien) { .extr1 = portal_pos(e.first),
                    .extr2 = portal_pos(e.second),
                    .joueur_l = owner(e) };
}

champ GameState::triangle_to_field(const itriple& t) const
{
    champ c;
    c.joueur_c = owner(t);
    unpack_triangle_pos(t, c.som1, c.som2, c.som3);
    return c;
}

void GameState::unpack_triangle_pos(const itriple& t,
                         position& a, position& b, position& c) const
{
    a = portal_pos(std::get<0>(t));
    b = portal_pos(std::get<1>(t));
    c = portal_pos(std::get<2>(t));
}

int GameState::field_area_x2(const itriple& field) const
{
    position a, b, c;
    unpack_triangle_pos(field, a, b, c);

    return abs(determinant(a, b, a, c));
}


int GameState::num_shields(int portal_id) const
{
    return portal_shields_[portal_id];
}

void GameState::add_shield(int portal_id)
{
    portal_shields_[portal_id]++;
}

int GameState::action_points(int player_id) const
{
    return player_info_.at(player_id).action_points;
}

int GameState::move_points(int player_id) const
{
    return player_info_.at(player_id).move_points;
}

void GameState::decrement_action_points(int player_id, int delta)
{
    player_info_.at(player_id).action_points -= delta;
}

void GameState::increment_move_points(int player_id, int delta)
{
    player_info_.at(player_id).move_points += delta;
}

const position& GameState::portal_pos(int portal_id) const
{
    return map_->get_portals()[portal_id];
}

const position& GameState::player_pos(int player_id) const
{
    return player_info_.at(player_id).pos;
}

void GameState::set_pos(int player_id, const position& position)
{
    player_info_.at(player_id).pos = position;
}


