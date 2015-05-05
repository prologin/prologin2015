/*
** Stechec project is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** The complete GNU General Public Licence Notice can be found as the
** `NOTICE' file in the root directory.
**
** Copyright (C) 2015 Prologin
*/

#include <stdlib.h>

#include "api.hh"
#include "actions.hh"

// global used in interface.cc
Api* api;

Api::Api(GameState* game_state, rules::Player_sptr player)
    : game_state_(game_state),
      player_(player)
{
    api = this;
}


///
// Déplace votre agent sur la case passée en argument.
//
erreur Api::deplacer(position dest)
{
    rules::IAction_sptr action(new ActionDeplacer(dest, player_->id));

    erreur err;
    if ((err = static_cast<erreur>(action->check(game_state_))) != OK)
        return err;

    actions_.add(action);
    game_state_set(action->apply(game_state_));
    return OK;
}

///
// Utilise un turbo.
//
erreur Api::utiliser_turbo()
{
    rules::IAction_sptr action(new ActionUtiliserTurbo(player_->id));

    erreur err;
    if ((err = static_cast<erreur>(action->check(game_state_))) != OK)
        return err;

    actions_.add(action);
    game_state_set(action->apply(game_state_));
    return OK;
}

///
// Capture le portail où est positionné votre agent.
//
erreur Api::capturer()
{
    rules::IAction_sptr action(new ActionCapturer(player_->id));

    erreur err;
    if ((err = static_cast<erreur>(action->check(game_state_))) != OK)
        return err;

    actions_.add(action);
    game_state_set(action->apply(game_state_));
    return OK;
}

///
// Crée un lien entre le portail où se trouve votre agent et le portail de destination donné en argument.
//
erreur Api::lier(position portail)
{
    rules::IAction_sptr action(new ActionLier(portail, player_->id));

    erreur err;
    if ((err = static_cast<erreur>(action->check(game_state_))) != OK)
        return err;

    actions_.add(action);
    game_state_set(action->apply(game_state_));
    return OK;
}

///
// Neutralise le portail où se trouve votre agent.
//
erreur Api::neutraliser()
{
    rules::IAction_sptr action(new ActionNeutraliser(player_->id));

    erreur err;
    if ((err = static_cast<erreur>(action->check(game_state_))) != OK)
        return err;

    actions_.add(action);
    game_state_set(action->apply(game_state_));
    return OK;
}

///
// Ajoute un bouclier au portail sur lequel se trouve votre agent.
//
erreur Api::ajouter_bouclier()
{
    rules::IAction_sptr action(new ActionAjouterBouclier(player_->id));

    erreur err;
    if ((err = static_cast<erreur>(action->check(game_state_))) != OK)
        return err;

    actions_.add(action);
    game_state_set(action->apply(game_state_));
    return OK;
}

///
// Renvoie la liste de tous les liens présents.
//
std::vector<lien> Api::liste_liens()
{
  // TODO
  abort();
}

///
// Renvoie la liste de tous les champs de contrôle.
//
std::vector<champ> Api::liste_champs()
{
  // TODO
  abort();
}

///
// Renvoie la liste de tous les portails de la carte.
//
std::vector<position> Api::liste_portails()
{
  // TODO
  abort();
}

///
// Renvoie la liste de tous les liens existants qui croisent un segment, entravant la création d'un lien.
//
std::vector<lien> Api::liens_bloquants(position ext1, position ext2)
{
  // TODO
  abort();
}

///
// Prend les positions de deux portails, et renvoie un booléen indiquant s'ils sont reliés. Le résultat est `false` lorsque l'une des deux positions ne repère pas un portail.
//
bool Api::lien_existe(position ext1, position ext2)
{
  // TODO
  abort();
}

///
// Renvoie un booléen indiquant si les 3 positions repèrent bien 3 portails tous reliés entre eux.
//
bool Api::champ_existe(position som1, position som2, position som3)
{
  // TODO
  abort();
}

///
// Renvoie un booléen indiquant si la case ``pos`` se trouve dans un champ.
//
bool Api::case_dans_champ(position pos)
{
  // TODO
  abort();
}

///
// Renvoie la liste des champs à l'intérieur desquels ``pos`` se trouve. Si la case est un portail, le résultat de ``case_champs`` sera disjoint de celui de ``champs_incidents_portail``.
//
std::vector<champ> Api::case_champs(position pos)
{
  // TODO
  abort();
}

///
// Renvoie le numéro du joueur correspondant au portail donné, -1 si le portail est neutre, -2 si la case n'est pas un portail. Vous pouvez utiliser cette fonction pour vérifier qu'une case donnée est bien un portail.
//
int Api::portail_joueur(position portail)
{
  // TODO
  abort();
}

///
// Renvoie le nombre de boucliers présents sur un portail (-2 si la case n'est pas un portail).
//
int Api::portail_boucliers(position portail)
{
  // TODO
  abort();
}

///
// Renvoie la liste de tous les liens dont le portail donné est une extrémité.
//
std::vector<lien> Api::liens_incidents_portail(position portail)
{
  // TODO
  abort();
}

///
// Renvoie la liste de tous les champs dont le portail donné est un sommet.
//
std::vector<champ> Api::champs_incidents_portail(position portail)
{
  // TODO
  abort();
}

///
// Renvoie la liste de tous les champs dont le lien donné est un côté. Si le segment n'est pas un lien présent, renvoie la liste de tous les champs que la création du lien ferait apparaître.
//
std::vector<champ> Api::champs_incidents_segment(position ext1, position ext2)
{
  // TODO
  abort();
}

///
// Renvoie la liste des portails capturés par votre adversaire au dernier tour.
//
std::vector<position> Api::hist_portails_captures()
{
  // TODO
  abort();
}

///
// Renvoie la liste des portails neutralisés par votre adversaire au dernier tour. Cela inclut toutes les utilisations de virus.
//
std::vector<position> Api::hist_portails_neutralises()
{
  // TODO
  abort();
}

///
// Renvoie la liste des liens créés par votre adversaire au dernier tour.
//
std::vector<lien> Api::hist_liens_crees()
{
  // TODO
  abort();
}

///
// Renvoie la liste des champs créés par votre adversaire au dernier tour.
//
std::vector<champ> Api::hist_champs_crees()
{
  // TODO
  abort();
}

///
// Renvoie la liste des positions où votre adversaire a ajouté des boucliers au dernier tour.
//
std::vector<position> Api::hist_boucliers_ajoutes()
{
  // TODO
  abort();
}

///
// Renvoie la distance entre deux positions
//
int Api::distance(position pos1, position pos2)
{
  // TODO
  abort();
}

///
// Renvoie le nombre de points que rapporte(rait) chaque tour un champ existant ou hypothétique.
//
int Api::score_triangle(position som1, position som2, position som3)
{
  // TODO
  abort();
}

///
// Indique si deux segments se croisent. Cette fonction correspond exactement à la condition d'interférence entre liens, c'est-à-dire qu'elle renvoie ``false`` si l'intersection est une extrémité des deux segments.
//
bool Api::intersection_segments(position a1, position a2, position b1, position b2)
{
  // TODO
  abort();
}

///
// Indique si un point se trouve à l'intérieur d'un triangle. Le critère coïncide avec celui de ``case_champs``.
//
bool Api::point_dans_triangle(position p, position som1, position som2, position som3)
{
  // TODO
  abort();
}

///
// Renvoie votre numéro de joueur.
//
int Api::moi()
{
  // TODO
  abort();
}

///
// Renvoie le numéro de votre adversaire.
//
int Api::adversaire()
{
  // TODO
  abort();
}

///
// Indique la position de l'agent du joueur désigné par le numéro ``id_joueur``.
//
position Api::position_agent(int id_joueur)
{
  // TODO
  abort();
}

///
// Indique votre nombre de points d'actions restants pour ce tour-ci.
//
int Api::points_action()
{
  // TODO
  abort();
}

///
// Indique votre nombre de points de déplacement restants pour ce tour-ci.
//
int Api::points_deplacement()
{
  // TODO
  abort();
}

///
// Renvoie le score du joueur désigné par le numéro ``id_joueur``.
//
int Api::score(int id_joueur)
{
  // TODO
  abort();
}

///
// Renvoie le numéro du tour actuel.
//
int Api::tour_actuel()
{
  // TODO
  abort();
}

///
// Annule la dernière action. Renvoie ``false`` quand il n'y a pas d'action à annuler ce tour-ci.
//
bool Api::annuler()
{
  // TODO
  abort();
}

///
// Affiche le contenu d'une valeur de type erreur
//

///
// Affiche le contenu d'une valeur de type position
//

///
// Affiche le contenu d'une valeur de type lien
//

///
// Affiche le contenu d'une valeur de type champ
//


