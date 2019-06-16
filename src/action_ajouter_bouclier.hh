#ifndef ACTION_AJOUTER_BOUCLIER_HH
#define ACTION_AJOUTER_BOUCLIER_HH

#include <rules/action.hh>

#include "actions.hh"
#include "constant.hh"
#include "game_state.hh"

class ActionAjouterBouclier : public rules::Action<GameState>
{
public:
    ActionAjouterBouclier(int player_id) : player_id_(player_id) {}
    ActionAjouterBouclier() {} // for register_action()

    int check(const GameState& st) const override;
    void apply_on(GameState* st) const override;

    void handle_buffer(utils::Buffer& buf) override { buf.handle(player_id_); }

    uint32_t player_id() const override { return player_id_; };
    uint32_t id() const override { return ID_ACTION_AJOUTER_BOUCLIER; }

private:
    int player_id_;
};

#endif // !ACTION_AJOUTER_BOUCLIER_HH
