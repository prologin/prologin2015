// FIXME License notice

#ifndef ACTIONS_HH
#define ACTIONS_HH

#include "action_ack.hh"
#include "action_capturer.hh"
#include "action_lier.hh"
#include "action_attaquer.hh"
#include "action_deplacer.hh"
#include "action_recharger.hh"
#include "action_ajouter_bouclier.hh"
#include "action_utiliser_virus.hh"
#include "action_utiliser_turbo.hh"

#include "constant.hh"

enum action_id {
    ID_ACTION_ACK,
    ID_ACTION_CAPTURER,
    ID_ACTION_LIER,
    ID_ACTION_ATTAQUER,
    ID_ACTION_DEPLACER,
    ID_ACTION_RECHARGER,
    ID_ACTION_AJOUTER_BOUCLIER,
    ID_ACTION_UTILISER_VIRUS,
    ID_ACTION_UTILISER_TURBO
};

#endif // !ACTIONS_HH
