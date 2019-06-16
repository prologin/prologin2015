#ifndef ACTION_LIER_HH
#define ACTION_LIER_HH

#include <rules/action.hh>

#include "actions.hh"
#include "constant.hh"
#include "game_state.hh"

class ActionLier : public rules::Action<GameState>
{
public:
    ActionLier(position portail, int player_id)
        : portail_(portail), player_id_(player_id)
    {}
    ActionLier() {} // for register_action()

    int check(const GameState& st) const override;
    void apply_on(GameState* st) const override;

    void handle_buffer(utils::Buffer& buf) override
    {
        buf.handle(portail_);
        buf.handle(player_id_);
    }

    uint32_t player_id() const override { return player_id_; };
    uint32_t id() const override { return ID_ACTION_LIER; }

private:
    position portail_;
    int player_id_;
};

#endif // !ACTION_LIER_HH
