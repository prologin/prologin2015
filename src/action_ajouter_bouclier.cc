// FIXME License notice

#include "actions.hh"

ActionAjouterBouclier::ActionAjouterBouclier(int player_id)
    : player_id_(player_id)
{
}

ActionAjouterBouclier::ActionAjouterBouclier()
    : player_id_(-1)
{
}

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

uint32_t ActionAjouterBouclier::player_id() const
{
    return player_id_;
}

uint32_t ActionAjouterBouclier::id() const
{
    return ID_ACTION_AJOUTER_BOUCLIER;
}

