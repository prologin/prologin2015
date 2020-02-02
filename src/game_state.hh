// FIXME License notice

#ifndef GAME_STATE_HH
#define GAME_STATE_HH

#include <cstdint>
#include <map>
#include <memory>

#include <rules/game-state.hh>
#include <rules/player.hh>

#include "graph.hh"
#include "map.hh"

// Game-specific information related to each player
struct player_info
{
    // Action an move points still available for the player for the current
    // turn.
    int action_points;
    int move_points;

    // Position of the player's agent.
    position pos;

    // Local score information
    int score;

    // Reference to the score in Stechec's player data structures, for
    // convenience.
    int* stechec_score;
};

// Structure to store a diff between the states at the start of the
// current turn and at the start of the previous one.
struct history_info
{
    // list of portals captured (resp. neutralised) during previous turn
    std::vector<position> hist_captured;
    std::vector<position> hist_neutralised;

    // list of links (resp. fields) created during previous turn
    std::vector<lien> hist_links;
    std::vector<champ> hist_fields;

    // list of shields added during previous turn
    std::vector<position> hist_shields;
};

class GameState : public rules::GameState
{
public:
    // Build a game state out of a input stream containing a description
    // of the map, and some players.
    GameState(std::istream& map_stream, const rules::Players& players);
    GameState* copy() const;

    // Return the current round number.
    int get_current_round() const;
    // Go to the next round: increment the current round number.
    void go_next_round();
    // Reset points at the start of a player's turn.
    void reset_points(int player_id);
    // After a player's turn has ended, reset points and update scores.
    // Doing both together avoids a recomputation of the list of triangles.
    void end_of_player_turn(int player_id);

    // Return false when it's still time for players to play, true otherwise.
    bool is_finished() const;

    // Accessor for Stechec players, used in the dumper.
    const rules::Players get_players() const { return players_; }
    // Return the ID for "player_id"'s opponent player.
    int get_opponent(int player_id) const;
    // Return the score for "player_id".
    int get_score(int player_id) const;
    // Add "delta" to "player_id"'s score ("delta" can be negative).
    void increment_score(int player_id, int delta);

    // Accessor for the map.
    const Map& map() const { return *map_; }
    // Accessor the graph for all edges/triangles created by players.
    const Graph& graph() const { return graph_; }
    Graph& graph() { return graph_; }

    // Return the player ID for the player that owns a portal.  Return -1 if
    // the portal is not owned by anyone.
    int owner(int portal_id) const;
    // Remove any ownership for some portal.  This also removes shields for
    // this portal.
    void neutralize(int portal_id);
    // Make "player_id" own "portal_id".  This also removes shields for this
    // portal.
    void capture(int portal_id, int player_id);

    // Return the owner of a link (edge) and of a field (triangle). Note that
    // it's the same as the owner of any involved portal, so these are
    // shortcuts.
    int owner(const ipair& link) const;
    int owner(const itriple& field) const;

    // Extract information from edges/triangles in order to produce the "lien"
    // and "champ" data structures.
    lien edge_to_link(const ipair& e) const;
    champ triangle_to_field(const itriple& t) const;

    // Helper to unpack triangles into portals.
    void unpack_triangle_pos(const itriple& t, position& a, position& b,
                             position& c) const;
    // Computes the area of the triangle spanned by a field,
    // multiplied by a factor of 2 to ensure that it is an integer
    int field_area_x2(const itriple& field) const;

    // Return the number of shieleds associated to "portal_id".
    int num_shields(int portal_id) const;
    // Increment the number of shields associated to "portal_id".
    void add_shield(int portal_id);

    // Return the number of action points still available for "player_id" for
    // the current turn.
    int action_points(int player_id) const;
    // Likewise for move points.
    int move_points(int player_id) const;

    // Decrement the number of action points still available for "player_id"
    // for the current turn by "delta".
    void decrement_action_points(int player_id, int delta);
    // Likewise for move points.
    void increment_move_points(int player_id, int delta);

    // Return the position for some portal.
    const position& portal_pos(int portal_id) const;
    // Return the position for some player.
    const position& player_pos(int player_id) const;
    // Move the agent for "player_id" to some position. This does _not_ update
    // the corresponding move points.
    void set_pos(int player_id, const position& position);

    const history_info& history() { return *history_; }

private:
    GameState(const GameState& st);

    // Array of all clients on this game.  Note that this also contains
    // spectators.
    rules::Players players_;

    int current_round_;

    // The game state at the begining of the round.
    std::shared_ptr<GameState> initial_state;

    // The Graph is an adjacency list which doesn't know anything about
    // its concrete realization in the plane; portals are represented
    // by IDs (ints).
    // Mapping portal IDs to positions on a grid is the responsibility
    // of the Map, which is supposed to be *constant* during the entirety
    // of the game (the data it holds is entirely given by the map file)
    // hence the shared_ptr.
    std::shared_ptr<const Map> map_;
    Graph graph_;

    // Mapping: portal ID -> ID of the player that owns the corresponding
    // portal, or -1 if no one owns it.
    std::vector<int> portal_player_;

    // Mapping: portal ID -> number of shields on the corresponding portal.
    std::vector<int8_t> portal_shields_;

    // Mapping: player ID -> player_info data structure.  Spectators are
    // missing from this mapping.
    std::map<int, player_info> player_info_;

    // The history is in a shared_ptr because it only refers to the previous
    // turn's events: it is constant during a turn.
    std::shared_ptr<history_info> history_;
};

#endif /* !GAME_STATE_HH */
