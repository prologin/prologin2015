#ifndef ACTION_DEPLACER_HH
#define ACTION_DEPLACER_HH

#include <rules/action.hh>

#include "actions.hh"
#include "constant.hh"
#include "game_state.hh"

class ActionDeplacer : public rules::Action<GameState>
{
public:
    ActionDeplacer(position dest, int player_id)
        : dest_(dest), player_id_(player_id)
    {}
    ActionDeplacer() {} // for register_action()

    int check(const GameState& st) const override;
    void apply_on(GameState* st) const override;

    void handle_buffer(utils::Buffer& buf) override
    {
        buf.handle(dest_);
        buf.handle(player_id_);
    }

    uint32_t player_id() const override { return player_id_; };
    uint32_t id() const override { return ID_ACTION_DEPLACER; }

private:
    // The move destination.
    position dest_;
    // The player that is moving.
    int player_id_;
};

#endif // !ACTION_DEPLACER_HH
