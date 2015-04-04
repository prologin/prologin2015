// FIXME License notice

#include "actions.hh"

#include "geometry.hh"

ActionDeplacer::ActionDeplacer(position dest, int player_id)
    : dest_(dest)
    , player_id_(player_id)
{
}

ActionDeplacer::ActionDeplacer()
    : dest_({-1,-1})
    , player_id_(-1)
{
}

int ActionDeplacer::check(const GameState* st) const
{
    CHECK_POSITION(dest_);
    int p = player_id_;
    if (l1_distance(st->player_pos(p), dest_) > st->move_points(p))
        return POSITION_ELOIGNEE;
    return OK;
}

void ActionDeplacer::handle_buffer(utils::Buffer& buf)
{
    buf.handle(dest_);
    buf.handle(player_id_);
}

void ActionDeplacer::apply_on(GameState* st) const
{
    st->set_pos(player_id_, dest);
    st->increment_move_points(player_id_, -l1_distance(TODO, dest_));
}

uint32_t ActionDeplacer::player_id() const
{
    return player_id_;
}

uint32_t ActionDeplacer::id() const
{
    return ID_ACTION_DEPLACER;
}

