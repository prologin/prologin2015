// FIXME License notice

#include "actions.hh"

ActionAttaquer::ActionAttaquer(int energie, int player_id)
    : energie_(energie)
    , player_id_(player_id)
{
}

ActionAttaquer::ActionAttaquer()
    : energie_(-1)
    , player_id_(-1)
{
}

int ActionAttaquer::check(const GameState* st) const
{
    // FIXME
    return 0;
}

void ActionAttaquer::handle_buffer(utils::Buffer& buf)
{
    buf.handle(energie_);
    buf.handle(player_id_);
}

void ActionAttaquer::apply_on(GameState* st) const
{
    // FIXME
}

uint32_t ActionAttaquer::player_id() const
{
    return player_id_;
}

uint32_t ActionAttaquer::id() const
{
    return ID_ACTION_ATTAQUER;
}
