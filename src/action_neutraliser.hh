#ifndef ACTION_NEUTRALISER_HH
#define ACTION_NEUTRALISER_HH

#include <rules/action.hh>

#include "actions.hh"
#include "constant.hh"
#include "game_state.hh"

class ActionNeutraliser : public rules::Action<GameState>
{
public:
    ActionNeutraliser(int player_id) : player_id_(player_id) {}
    ActionNeutraliser() {} // for register_action()

    int check(const GameState& st) const override;
    void apply_on(GameState* st) const override;

    void handle_buffer(utils::Buffer& buf) override { buf.handle(player_id_); }

    uint32_t player_id() const override { return player_id_; };
    uint32_t id() const override { return ID_ACTION_NEUTRALISER; }

private:
    int player_id_;
};

#endif // !ACTION_NEUTRALISER_HH
