// FIXME License notice

#ifndef ACTION_DETRUIRE_HH
#define ACTION_DETRUIRE_HH

#include <rules/action.hh>

#include "game_state.hh"
#include "constant.hh"

class ActionDetruire : public rules::Action<GameState>
{
public:
    ActionDetruire(int player_id);
    ActionDetruire();

    virtual int check(const GameState* st) const;
    virtual void handle_buffer(utils::Buffer& buf);
    virtual void apply_on(GameState* st) const;

    uint32_t player_id() const;
    uint32_t id() const;

private:
    int player_id_;
};

#endif // !ACTION_DETRUIRE_HH
