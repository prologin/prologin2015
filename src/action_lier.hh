// FIXME License notice

#ifndef ACTION_LIER_HH
#define ACTION_LIER_HH

#include <rules/action.hh>

#include "game_state.hh"
#include "constant.hh"

class ActionLier : public rules::Action<GameState>
{
public:
    ActionLier(position portail, int player_id);
    ActionLier();

    virtual int check(const GameState* st) const;
    virtual void handle_buffer(utils::Buffer& buf);
    virtual void apply_on(GameState* st) const;

    uint32_t player_id() const;
    uint32_t id() const;

private:
    position portail_;
    int player_id_;
};

#endif // !ACTION_LIER_HH

