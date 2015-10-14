#ifndef RULES_RULES_HH_
#define RULES_RULES_HH_

#include <utils/dll.hh>
#include <utils/sandbox.hh>
#include <rules/options.hh>
#include <rules/client-messenger.hh>
#include <rules/server-messenger.hh>
#include <rules/player.hh>
#include <rules/rules.hh>
#include <rules/actions.hh>

#include "api.hh"

typedef void (*f_champion_partie_init)();
typedef void (*f_champion_jouer_tour)();
typedef void (*f_champion_partie_fin)();

class Rules : public rules::TurnBasedRules
{
public:
    explicit Rules(const rules::Options opt);
    virtual ~Rules();

    virtual rules::Actions* get_actions();
    virtual void apply_action(const rules::IAction_sptr& action);
    virtual bool is_finished();

    virtual void at_start();
    virtual void at_player_start();
    virtual void at_spectator_start();
    virtual void at_player_end();
    virtual void at_spectator_end();

    virtual void player_turn();
    virtual void spectator_turn();

    virtual void start_of_round();
    virtual void end_of_round();

    virtual void start_of_player_turn(uint32_t);
    virtual void end_of_player_turn(uint32_t);

    virtual void dump_state(std::ostream& out);

protected:
    f_champion_partie_init champion_partie_init_;
    f_champion_jouer_tour champion_jouer_tour_;
    f_champion_partie_fin champion_partie_fin_;

private:
    utils::DLL* champion_dll_;
    Api* api_;
    utils::Sandbox sandbox_;
};

#endif // !RULES_RULES_HH_
