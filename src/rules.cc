#include <cstdlib>
#include <fstream>

#include <rules/actions.hh>
#include <rules/player.hh>
#include <utils/log.hh>

#include "actions.hh"
#include "errors.hh"
#include "rules.hh"

Rules::Rules(const rules::Options opt) : TurnBasedRules(opt), sandbox_(opt.time)
{
    if (!opt.champion_lib.empty())
    {
        champion_dll_ = std::make_unique<utils::DLL>(opt.champion_lib);
        champion_partie_init_ =
            champion_dll_->get<f_champion_partie_init>("partie_init");
        champion_jouer_tour_ =
            champion_dll_->get<f_champion_jouer_tour>("jouer_tour");
        champion_partie_fin_ =
            champion_dll_->get<f_champion_partie_fin>("partie_fin");
    }

    std::ifstream ifs(opt.map_file);
    if (!ifs.is_open())
        FATAL("Cannot open file: %s", opt.map_file.c_str());

    auto game_state = std::make_unique<GameState>(ifs, opt.players);
    api_ = std::make_unique<Api>(std::move(game_state), opt.player);
    register_actions();
}

void Rules::register_actions()
{
    // Register actions
    api_->actions()->register_action(
        ID_ACTION_DEPLACER,
        []() -> rules::IAction* { return new ActionDeplacer(); });
    api_->actions()->register_action(
        ID_ACTION_UTILISER_TURBO,
        []() -> rules::IAction* { return new ActionUtiliserTurbo(); });
    api_->actions()->register_action(
        ID_ACTION_CAPTURER,
        []() -> rules::IAction* { return new ActionCapturer(); });
    api_->actions()->register_action(
        ID_ACTION_LIER, []() -> rules::IAction* { return new ActionLier(); });
    api_->actions()->register_action(
        ID_ACTION_NEUTRALISER,
        []() -> rules::IAction* { return new ActionNeutraliser(); });
    api_->actions()->register_action(
        ID_ACTION_AJOUTER_BOUCLIER,
        []() -> rules::IAction* { return new ActionAjouterBouclier(); });
}

rules::Actions* Rules::get_actions()
{
    return api_->actions();
}

void Rules::apply_action(const rules::IAction_sptr& action)
{
    // When receiving an action, the API should have already checked that it
    // is valid. We recheck that for the current gamestate here to avoid weird
    // client/server desynchronizations and make sure the gamestate is always
    // consistent across the clients and the server.

    int err = action->check(api_->game_state());

    if (err)
        FATAL("Synchronization error: received action %d from player %d, but "
              "check() on current gamestate returned %d.",
              action->id(), action->player_id(), err);

    api_->game_state_apply(action);
}

bool Rules::is_finished()
{
    return api_->game_state().is_finished();
}

void Rules::at_start()
{
    api_->game_state().go_next_round();
}

void Rules::at_player_start(rules::ClientMessenger_sptr)
{
    try
    {
        sandbox_.execute(champion_partie_init_);
    }
    catch (utils::SandboxTimeout&)
    {
        FATAL("partie_init: timeout");
    }
}

void Rules::at_spectator_start(rules::ClientMessenger_sptr)
{
    champion_partie_init_();
}

void Rules::at_player_end(rules::ClientMessenger_sptr)
{
    try
    {
        sandbox_.execute(champion_partie_fin_);
    }
    catch (utils::SandboxTimeout&)
    {
        FATAL("partie_fin: timeout");
    }
}

void Rules::at_spectator_end(rules::ClientMessenger_sptr)
{
    champion_partie_fin_();
}

void Rules::player_turn()
{
    try
    {
        sandbox_.execute(champion_jouer_tour_);
    }
    catch (utils::SandboxTimeout&)
    {
        FATAL("partie_fin: timeout");
    }
}

void Rules::spectator_turn()
{
    champion_jouer_tour_();
}

void Rules::start_of_round()
{
    INFO("ROUND %d", api_->game_state().get_current_round());
}

void Rules::end_of_round()
{
    api_->game_state().go_next_round();
}

void Rules::start_of_player_turn(uint32_t player_id)
{
    api_->game_state().reset_points(static_cast<int>(player_id));
}

void Rules::end_of_player_turn(uint32_t player_id)
{
    api_->game_state().end_of_player_turn(static_cast<int>(player_id));

    // Clear previous game states at the end of each turn (half-round)
    // We need the previous game states only for undo and history, therefore
    // old states are not needed anymore after the turn ends.
    api_->clear_old_game_states();
}

void Rules::dump_state(std::ostream& out)
{
    char* line = api_->get_dump();
    out << line << std::endl;
    free(line);
}
