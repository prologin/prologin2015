#include "actions.hh"

#include "geometry.hh"

int ActionDeplacer::check(const GameState* st) const
{
    if (!Map::valid_position(dest_))
        return POSITION_INVALIDE;

    int p = player_id_;
    if (l1_distance(st->player_pos(p), dest_) > st->move_points(p))
        return POSITION_ELOIGNEE;
    return OK;
}

void ActionDeplacer::apply_on(GameState* st) const
{
    // Compute the distance *before* moving the player: this would affect the
    // distance...
    st->increment_move_points(player_id_,
                              -l1_distance(st->player_pos(player_id_), dest_));
    st->set_pos(player_id_, dest_);
}
