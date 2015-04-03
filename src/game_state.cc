// FIXME License notice

#include "game_state.hh"
#include "constant.hh"

GameState::GameState(Map* map, rules::Players_sptr players)
    : rules::GameState()
    , players_(players)
    , map_(map)
    , graph_(map->num_portals())
    , current_turn_(0)
{
    // FIXME
}

GameState::GameState(const GameState& st)
    : rules::GameState(st)
    , players_(st.players_)
    , map_(st.map_)
    , current_turn_(st.current_turn_)
    , graph_(st.graph_)
{
    // FIXME
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


GameState::~GameState()
{
    // FIXME
}
