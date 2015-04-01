// FIXME License notice

#ifndef ACTION_RECHARGER_HH
#define ACTION_RECHARGER_HH

#include <rules/action.hh>

#include "actions.hh"
#include "game_state.hh"
#include "constant.hh"

class ActionRecharger : public rules::Action<GameState>
{
public:
    ActionRecharger(position portail, int player_id);
    ActionRecharger();

    virtual int check(const GameState* st) const;
    virtual void handle_buffer(utils::Buffer& buf);
    virtual void apply_on(GameState* st) const;

    uint32_t player_id() const;
    uint32_t id() const;

private:
    position portail_;
    int player_id_;
};

#endif // !ACTION_RECHARGER_HH

