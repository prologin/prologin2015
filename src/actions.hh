#ifndef ACTIONS_HH
#define ACTIONS_HH

enum action_id {
    ID_ACTION_DEPLACER,
    ID_ACTION_UTILISER_TURBO,
    ID_ACTION_CAPTURER,
    ID_ACTION_LIER,
    ID_ACTION_NEUTRALISER,
    ID_ACTION_AJOUTER_BOUCLIER
};

#include "action_deplacer.hh"
#include "action_utiliser_turbo.hh"
#include "action_capturer.hh"
#include "action_lier.hh"
#include "action_neutraliser.hh"
#include "action_ajouter_bouclier.hh"

#endif // !ACTIONS_HH
