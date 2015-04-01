#include "rules.hh"
#include "actions.hh"

Rules::Rules(const rules::Options opt)
    : // FIXME inheritance
    , sandbox_(opt.time)
{
    if (!opt.champion_lib.empty())
    {
        champion_dll_ = new utils::DLL(opt.champion_lib);

        // FIXME
        // register user functions
    }
    else
        champion_dll_ = nullptr;
    
    // Init gamestate
    GameState* game_state = new GameState(opt.players);

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

    // FIXME
}

Rules::~Rules()
{
    // FIXME

    delete champion_dll_;
}


// FIXME
// If you inherit from TurnBasedRules or SynchronousRules,
// keep 1) and delete 2) ; else, keep 2) and delete 1)

// 1)
rules::Actions* Rules::get_actions()
{
    // FIXME
    return api_->actions();
}

void Rules::apply_action(const rules::IAction_sptr& action)
{
    // FIXME
    api_->game_state_set(action->apply(api_->game_state()));
}

bool Rules::is_finished()
{
    // FIXME
    return true;
}
// end 1)

// 2)
void Rules::client_loop(rules::ClientMessenger_sptr msgr)
{
    // FIXME
}

void Rules::spectator_loop(rules::ClientMessenger_sptr msgr)
{
    // FIXME
}

void Rules::server_loop(rules::ServerMessenger_sptr msgr)
{
    // FIXME
}

// end 2)

