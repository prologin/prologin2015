#ifndef ACTION_AJOUTER_BOUCLIER_HH
#define ACTION_AJOUTER_BOUCLIER_HH

#include <rules/action.hh>

#include "game_state.hh"
#include "constant.hh"

class ActionAjouterBouclier : public rules::Action<GameState>
{
public:
    ActionAjouterBouclier(int player_id) : player_id_(player_id) {}
    ActionAjouterBouclier() {} // for register_action()

    virtual int check(const GameState* st) const;
    virtual void apply_on(GameState* st) const;

    virtual void handle_buffer(utils::Buffer& buf)
    {
        buf.handle(player_id_);
    }

    uint32_t player_id() const { return player_id_; };
    uint32_t id() const { return ID_ACTION_AJOUTER_BOUCLIER; }

private:
    int player_id_;
};

#endif // !ACTION_AJOUTER_BOUCLIER_HH
