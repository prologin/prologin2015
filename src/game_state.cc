// FIXME License notice

#include <stdexcept>

#include "game_state.hh"
#include "constant.hh"
#include "geometry.hh"
#include "errors.hh"

GameState::GameState(Map* map, rules::Players_sptr players)
    : rules::GameState()
    , players_(players)
    , current_turn_(0)
    , map_(map)
    , graph_(map->num_portals())
    , portal_player_(map->num_portals(), -1)
    , portal_shields_(map->num_portals(), 0)
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
    , current_turn_(st.current_turn_)
    , map_(st.map_)
    , graph_(st.graph_)
    , portal_player_(st.portal_player_)
    , portal_shields_(st.portal_shields_)
    , player_info_(st.player_info_)
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

int GameState::get_current_turn() const
{
    return current_turn_;
}

void GameState::go_next_turn()
{
    ++current_turn_;
}

void GameState::end_of_player_turn(int player_id)
{
    // Check that the player_id refers to an actual player
    // Raise an exception if it's not the case
    // CHECK should we add this to all other functions which take a player id?
    auto iter = player_info_.find(player_id);
    if (iter == player_info_.end())
        throw InvalidPlayer(player_id);

    player_info& pi = iter->second;

    // Reset points
    // This should actually be done at the start of a player's turn
    // but since Rules::start_of_player_turn doesn't exist
    // it ends up here
    pi.action_points = NB_POINTS_ACTION;
    pi.move_points = NB_POINTS_DEPLACEMENT;

    // Update score with area covered by fields
    int area_x2 = 0;
    auto triangles = graph_.triangles();
    for (auto& t : triangles)
    {
        if (owner(t) == player_id)
            area_x2 += field_area_x2(t);
    }
    increment_score(player_id, (POINTS_CHAMP/2) * area_x2);
}

bool GameState::is_finished() const
{
    return current_turn_ > NB_TOURS;
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


