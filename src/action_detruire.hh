#ifndef ACTION_DETRUIRE_HH
#define ACTION_DETRUIRE_HH

#include <rules/action.hh>

#include "actions.hh"
#include "game_state.hh"
#include "constant.hh"

class ActionDetruire : public rules::Action<GameState>
{
public:
    ActionDetruire(int player_id) : player_id_(player_id) {}
    ActionDetruire() {} // for register_action()

    virtual int check(const GameState* st) const;
    virtual void apply_on(GameState* st) const;

    virtual void handle_buffer(utils::Buffer& buf)
    {
        buf.handle(player_id_);
    }

    uint32_t player_id() const { return player_id_; };
    uint32_t id() const { return ID_ACTION_DETRUIRE; }

private:
    int player_id_;
};

#endif // !ACTION_DETRUIRE_HH
