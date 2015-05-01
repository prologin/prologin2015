#include <fstream>

#include <utils/log.hh>
#include <rules/player.hh>
#include <rules/actions.hh>

#include "rules.hh"
#include "actions.hh"
#include "errors.hh"

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
    std::ifstream ifs(opt.map_file);
    map->load(ifs);

    // Init gamestate
    GameState* game_state = new GameState(map, opt.players);

    // Init API
    api_ = new Api(game_state, opt.player);

    // Register actions
    api_->actions()->register_action(
        ID_ACTION_CAPTURER,
        []() -> rules::IAction* { return new ActionCapturer(); }
        );
    api_->actions()->register_action(
        ID_ACTION_LIER,
        []() -> rules::IAction* { return new ActionLier(); }
        );
    api_->actions()->register_action(
        ID_ACTION_NEUTRALISER,
        []() -> rules::IAction* { return new ActionNeutraliser(); }
        );
    api_->actions()->register_action(
        ID_ACTION_DEPLACER,
        []() -> rules::IAction* { return new ActionDeplacer(); }
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
    api_->game_state()->go_next_turn();
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
    // No ack?
}

void Rules::start_of_turn()
{
    INFO("TURN %d", api_->game_state()->get_current_turn());
}

void Rules::end_of_turn()
{
    api_->game_state()->go_next_turn();
}

void Rules::end_of_player_turn(uint32_t player_id)
{
    // The player_id may be a spectator,
    // in which case this method will raise InvalidPlayer.
    // We just have to ignore this exception.
    try
    {
        api_->game_state()->end_of_player_turn(static_cast<int>(player_id));
    }
    catch (const InvalidPlayer& exn) { }

    // Clear the list of game states at the end of each turn (half-round)
    // We need the linked list of game states only for undo and history,
    // therefore old states are not needed anymore after the turn ends.
    // This is outside of the try block b/c it also concerns spectators.
    api_->game_state()->clear_old_version();
}
