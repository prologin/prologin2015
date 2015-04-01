// FIXME License notice

#include "action_ajouter_bouclier.hh"

ActionAjouterBouclier::ActionAjouterBouclier(int player_id)
    : player_id_(player_id)
{
}

ActionAjouterBouclier::ActionAjouterBouclier()
    : player_id_(FIXME)
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

