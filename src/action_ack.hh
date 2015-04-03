#ifndef ACTION_ACK_HH_

#define ACTION_ACK_HH_

#include <rules/action.hh>

#include "game_state.hh"
#include "constant.hh"

class ActionAck : public rules::Action<GameState>
{
public:
    ActionAck(int player);
    ActionAck();

    virtual int check(const GameState*) const { return 0; }
    virtual void handle_buffer(utils::Buffer&);

    uint32_t player_id() const;
    uint32_t id() const

protected:
    virtual void apply_on(GameState*) const { }

protected:
    int player_;
    int id_;
};

#endif /* !ACTION_ACK_HH_ */
