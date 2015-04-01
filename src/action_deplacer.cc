// FIXME License notice

#include "action_deplacer.hh"

ActionDeplacer::ActionDeplacer(position dest, int player_id)
    : dest_(dest)
    , player_id_(player_id)
{
}

ActionDeplacer::ActionDeplacer()
    : dest_(FIXME)
    , player_id_(FIXME)
{
}

int ActionDeplacer::check(const GameState* st) const
{
    // FIXME
    return 0;
}

void ActionDeplacer::handle_buffer(utils::Buffer& buf)
{
    buf.handle(dest_);
    buf.handle(player_id_);
}

void ActionDeplacer::apply_on(GameState* st) const
{
    // FIXME
}

uint32_t ActionDeplacer::player_id() const
{
    return player_id_;
}

uint32_t ActionDeplacer::id() const
{
    return ID_ACTION_DEPLACER;
}

