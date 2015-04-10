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
    // Build a game state out of a map and some players. The ownership of "map"
    // is transferred to the new GameState (i.e. the caller must not free it
    // nor reference it anymore.
    GameState(Map* map, rules::Players_sptr players);
    GameState(const GameState& st);
    virtual rules::GameState* copy() const;
    ~GameState();

    int get_current_turn() const;
    void increment_turn();

    bool is_finished() const;

    rules::Players_sptr get_players() const { return players_; }
    int get_opponent(int player_id) const;
    int get_score(int player_id) const;
    void increment_score(int player_id, int delta);

    const Graph& graph() const { return graph_; }
    Graph& graph() { return graph_; }
    const Map& map() const { return *map_; }
    Map& map() { return *map_; }

    int owner(int portal_id) const;
    void neutralize(int portal_id);
    void capture(int portal_id, int player_id);

    int owner(const ipair& link) const;
    int owner(const itriple& field) const;
    lien edge_to_link(const ipair& e) const;
    champ triangle_to_field(const itriple& t) const;

    void unpack_triangle_pos(const itriple& t,
                             position& a, position& b, position& c) const;
    int field_area_x2(const itriple& field) const;
    
    int num_shields(int portal_id) const;
    void add_shield(int portal_id);

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
    std::vector<int8_t> portal_shields_;

    std::map<int, player_info> player_info_;
};

#endif /* !GAME_STATE_HH */

