#include "actions.hh"

int ActionAjouterBouclier::check(const GameState* st) const
{
    // FIXME
    return 0;
}

void ActionAjouterBouclier::handle_buffer(utils::Buffer& buf)
{
    buf.handle(player_id_);
}

void ActionAjouterBouclier::apply_on(GameState* st) const
{
    // FIXME
}
