#ifndef ACTION_UTILISER_VIRUS_HH
#define ACTION_UTILISER_VIRUS_HH

#include <rules/action.hh>

#include "game_state.hh"
#include "constant.hh"

class ActionUtiliserVirus : public rules::Action<GameState>
{
public:
    ActionUtiliserVirus(int player_id) : player_id_(player_id) {}
    ActionUtiliserVirus() {} // for register_action()

    virtual int check(const GameState* st) const;
    virtual void apply_on(GameState* st) const;

    virtual void handle_buffer(utils::Buffer& buf)
    {
       buf.handle(player_id_);
    }

    uint32_t player_id() const { return player_id_ };
    uint32_t id() const { return ID_ACTION_UTILISER_VIRUS; }

private:
    int player_id_;
};

#endif // !ACTION_UTILISER_VIRUS_HH
