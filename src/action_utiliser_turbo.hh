// FIXME License notice

#ifndef ACTION_UTILISER_TURBO_HH
#define ACTION_UTILISER_TURBO_HH

#include <rules/action.hh>

#include "actions.hh"
#include "game_state.hh"
#include "constant.hh"

class ActionUtiliserTurbo : public rules::Action<GameState>
{
public:
    ActionUtiliserTurbo(int player_id);
    ActionUtiliserTurbo();

    virtual int check(const GameState* st) const;
    virtual void handle_buffer(utils::Buffer& buf);
    virtual void apply_on(GameState* st) const;

    uint32_t player_id() const;
    uint32_t id() const;

private:
    int player_id_;
};

#endif // !ACTION_UTILISER_TURBO_HH

