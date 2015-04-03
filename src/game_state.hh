// FIXME License notice

#ifndef GAME_STATE_HH
#define GAME_STATE_HH

#include <memory>

#include <rules/game-state.hh>
#include <rules/player.hh>

#include "map.hh"
#include "graph.hh"

class GameState : public rules::GameState
{
public:
    GameState(Map* map, rules::Players_sptr players);
    GameState(const GameState& st);
    virtual rules::GameState* copy() const;
    ~GameState();

    int get_current_turn() const;
    void increment_turn();

    bool is_finished() const;

private:
    rules::Players_sptr players_;
    std::shared_ptr<Map> map_;
    Graph graph_;
    int current_turn_;
};

#endif /* !GAME_STATE_HH */

