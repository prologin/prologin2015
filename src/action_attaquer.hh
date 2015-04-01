// FIXME License notice

#ifndef ACTION_ATTAQUER_HH
#define ACTION_ATTAQUER_HH

#include <rules/action.hh>

#include "actions.hh"
#include "game_state.hh"
#include "constant.hh"

class ActionAttaquer : public rules::Action<GameState>
{
public:
    ActionAttaquer(int energie, int player_id);
    ActionAttaquer();

    virtual int check(const GameState* st) const;
    virtual void handle_buffer(utils::Buffer& buf);
    virtual void apply_on(GameState* st) const;

    uint32_t player_id() const;
    uint32_t id() const;

private:
    int energie_;
    int player_id_;
};

#endif // !ACTION_ATTAQUER_HH

