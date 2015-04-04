// FIXME License notice

#ifndef GAME_STATE_HH
#define GAME_STATE_HH

#include <cstdint>
#include <memory>
#include <map>

#include <rules/game-state.hh>
#include <rules/player.hh>

#include "map.hh"
#include "graph.hh"

struct player_info
{
    int action_points;
    int move_points;
    position pos;
    int *score;
};

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

    int get_opponent(int player_id) const;
    int get_score(int player_id) const;
    void increment_score(int player_id, int delta);

    const Graph& graph() const { return graph_; }
    Graph& graph() { return graph_; }
    const Map& map() const { return map_; }
    Map& map() { return map_; }

    int portal_energy(int portal_id) const;
    int owner(int portal_id) const;
    void increment_energy(int portal_id, int delta);
    void neutralize(int portal_id);
    void capture(int portal_id, int player_id);

    int action_points(int player_id) const;
    int move_points(int player_id) const;
    void decrement_action_points(int player_id, int delta);
    void increment_move_points(int player_id, int delta);

    const position& portal_pos(int portal_id) const;
    const position& player_pos(int player_id) const;
    void set_pos(int player_id, const position& position);

private:
    rules::Players_sptr players_;
    int current_turn_;

    std::shared_ptr<Map> map_;
    Graph graph_;

    std::vector<int> portal_player_;
    // std::vector<int8_t> portal_shields_;
    std::vector<int> portal_energy_;

    std::map<int, player_info> player_info_;
};

#endif /* !GAME_STATE_HH */

