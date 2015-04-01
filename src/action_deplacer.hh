// FIXME License notice

#ifndef ACTION_DEPLACER_HH
#define ACTION_DEPLACER_HH

#include <rules/action.hh>

#include "game_state.hh"
#include "constant.hh"

class ActionDeplacer : public rules::Action<GameState>
{
public:
    ActionDeplacer(position dest, int player_id);
    ActionDeplacer();

    virtual int check(const GameState* st) const;
    virtual void handle_buffer(utils::Buffer& buf);
    virtual void apply_on(GameState* st) const;

    uint32_t player_id() const;
    uint32_t id() const;

private:
    position dest_;
    int player_id_;
};

#endif // !ACTION_DEPLACER_HH

