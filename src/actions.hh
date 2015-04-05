#ifndef ACTIONS_HH
#define ACTIONS_HH

enum action_id {
    ID_ACTION_CAPTURER,
    ID_ACTION_LIER,
    ID_ACTION_DETRUIRE,
    ID_ACTION_DEPLACER,
    ID_ACTION_AJOUTER_BOUCLIER,
    ID_ACTION_UTILISER_VIRUS,
    ID_ACTION_UTILISER_TURBO
};

#include "action_capturer.hh"
#include "action_lier.hh"
#include "action_detruire.hh"
#include "action_deplacer.hh"
#include "action_ajouter_bouclier.hh"
#include "action_utiliser_virus.hh"
#include "action_utiliser_turbo.hh"

#endif // !ACTIONS_HH
