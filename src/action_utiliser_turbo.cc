#include "actions.hh"

int ActionUtiliserTurbo::check(const GameState* st) const
{
    // Check action points
    if (st->action_points(player_id_) < (COUT_TURBO)) return PA_INSUFFISANTS;

    return OK;
}

void ActionUtiliserTurbo::apply_on(GameState* st) const
{
    // Consume action points
    st->decrement_action_points(player_id_, COUT_TURBO);

    st->increment_move_points(player_id_, 1);
}
