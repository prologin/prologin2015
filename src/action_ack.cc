#include "actions.hh"

ActionAck::ActionAck(int player)
    : player_(player)
{
}

ActionAck::ActionAck()
    : player_(-1)
{
}

void ActionAck::handle_buffer(utils::Buffer& buf)
{
    buf.handle(player_);
}

uint32_t ActionAck::player_id() const
{
    return player_;
}
uint32_t ActionAck::id() const
{
    return ID_ACTION_ACK;
}
