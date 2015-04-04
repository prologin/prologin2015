#include <fstream>

#include <utils/log.hh>
#include <rules/player.hh>
#include <rules/actions.hh>

#include "rules.hh"
#include "actions.hh"

Rules::Rules(const rules::Options opt)
    : TurnBasedRules(opt)
    , sandbox_(opt.time)
{
    if (!opt.champion_lib.empty())
    {
        champion_dll_ = new utils::DLL(opt.champion_lib);
        champion_partie_init_ =
            champion_dll_->get<f_champion_partie_init>("partie_init");
        champion_jouer_tour_ =
            champion_dll_->get<f_champion_jouer_tour>("jouer_tour");
        champion_partie_fin_ =
            champion_dll_->get<f_champion_partie_fin>("partie_fin");
    }
    else
        champion_dll_ = nullptr;

    Map* map = new Map;
    // std::ifstream ifs(opt.map_file);
    // map->load(ifs);
    map->init_stupid_map();

    // Init gamestate
    GameState* game_state = new GameState(map, opt.players);

    // Init API
    api_ = new Api(game_state, opt.player);

    // Register actions
    api_->actions()->register_action(
        ID_ACTION_ACK,
        []() -> rules::IAction* { return new ActionAck(); }
        );
    api_->actions()->register_action(
        ID_ACTION_CAPTURER,
        []() -> rules::IAction* { return new ActionCapturer(); }
        );
    api_->actions()->register_action(
        ID_ACTION_LIER,
        []() -> rules::IAction* { return new ActionLier(); }
        );
    api_->actions()->register_action(
        ID_ACTION_ATTAQUER,
        []() -> rules::IAction* { return new ActionAttaquer(); }
        );
    api_->actions()->register_action(
        ID_ACTION_DEPLACER,
        []() -> rules::IAction* { return new ActionDeplacer(); }
        );
    api_->actions()->register_action(
        ID_ACTION_RECHARGER,
        []() -> rules::IAction* { return new ActionRecharger(); }
        );
    api_->actions()->register_action(
        ID_ACTION_AJOUTER_BOUCLIER,
        []() -> rules::IAction* { return new ActionAjouterBouclier(); }
        );
    api_->actions()->register_action(
        ID_ACTION_UTILISER_VIRUS,
        []() -> rules::IAction* { return new ActionUtiliserVirus(); }
        );
    api_->actions()->register_action(
        ID_ACTION_UTILISER_TURBO,
        []() -> rules::IAction* { return new ActionUtiliserTurbo(); }
        );
}

Rules::~Rules()
{
    delete champion_dll_; // no effect if champion_ == nullptr
    delete api_;
}

rules::Actions* Rules::get_actions()
{
    return api_->actions();
}

void Rules::apply_action(const rules::IAction_sptr& action)
{
    api_->game_state_set(action->apply(api_->game_state()));
}

bool Rules::is_finished()
{
    return api_->game_state()->is_finished();
}

void Rules::at_start()
{
    api_->game_state()->increment_turn();
}

void Rules::at_client_start()
{
    sandbox_.execute(champion_partie_init_);
}

void Rules::at_spectator_start()
{
    champion_partie_init_();
}

void Rules::at_client_end()
{
    sandbox_.execute(champion_partie_fin_);
}

void Rules::at_spectator_end()
{
    champion_partie_fin_();
}

void Rules::player_turn()
{
    sandbox_.execute(champion_jouer_tour_);
}

void Rules::spectator_turn()
{
    champion_jouer_tour_();
    // CHECK: j'ai pas compris comment ça marche ce truc
    api_->actions()->add(
            rules::IAction_sptr(new ActionAck(api_->player()->id)));
}

void Rules::start_of_turn()
{
    INFO("TURN %d", api_->game_state()->get_current_turn());
}

void Rules::end_of_turn()
{
    api_->game_state()->increment_turn();
}
