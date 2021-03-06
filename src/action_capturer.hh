#ifndef ACTION_CAPTURER_HH
#define ACTION_CAPTURER_HH

#include <rules/action.hh>

#include "actions.hh"
#include "constant.hh"
#include "game_state.hh"

class ActionCapturer : public rules::Action<GameState>
{
public:
    ActionCapturer(int player_id) : player_id_(player_id) {}
    ActionCapturer() {} // for register_action()

    int check(const GameState& st) const override;
    void apply_on(GameState* st) const override;

    void handle_buffer(utils::Buffer& buf) override { buf.handle(player_id_); }

    uint32_t player_id() const override { return player_id_; };
    uint32_t id() const override { return ID_ACTION_CAPTURER; }

private:
    // The player that is trying to seize a portal.  No need for a portal ID
    // nor a portal position: players can only seize portals when they are on
    // the same cell.
    int player_id_;
};

#endif // !ACTION_CAPTURER_HH
