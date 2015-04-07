// FIXME License notice

#include "game_state.hh"
#include "constant.hh"

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

void GameState::increment_turn()
{
    current_turn_++;
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


