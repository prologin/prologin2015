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
#include <algorithm>

#include "api.hh"

#include "actions.hh"
#include "dumper.hh"
#include "geometry.hh"

// global used in interface.cc
Api* api;

Api::Api(GameState* game_state, rules::Player_sptr player)
    : game_state_(game_state),
      player_(player)
{
    api = this;
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
// Détruit le portail où se trouve votre agent.
//
erreur Api::detruire()
{
    rules::IAction_sptr action(new ActionDetruire(player_->id));

    erreur err;
    if ((err = static_cast<erreur>(action->check(game_state_))) != OK)
        return err;

    actions_.add(action);
    game_state_set(action->apply(game_state_));
    return OK;
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
// Fait passer le portail où se situe votre agent à l'autre joueur.
//
erreur Api::utiliser_virus()
{
    rules::IAction_sptr action(new ActionUtiliserVirus(player_->id));

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
// Renvoie la liste de tous les liens présents.
//
std::vector<lien> Api::liste_liens()
{
    // TODO tester

    auto edges = game_state_->graph().edges();
    std::vector<lien> links; 
    std::transform (edges.cbegin(), edges.cend(), links.begin(),
                    [this](const ipair& e)
                    { return game_state_->edge_to_link(e); });
    return links;
}

///
// Renvoie la liste de tous les champs de contrôle.
//
std::vector<champ> Api::liste_champs()
{
    // TODO tester

    auto triangles = game_state_->graph().triangles();
    std::vector<champ> fields(triangles.size());
    std::transform (triangles.cbegin(), triangles.cend(), fields.begin(),
                    [this](const itriple& t)
                    { return game_state_->triangle_to_field(t); });
    return fields;
}

///
// Renvoie la liste de tous les portails de la carte.
//
std::vector<position> Api::liste_portails()
{
    return game_state_->map().get_portals();
}

///
// Renvoie la liste de tous les liens existants qui croisent un segment, entravant la création d'un lien.
//
std::vector<lien> Api::liens_bloquants(position ext1, position ext2)
{
    // TODO tester

    auto edges = game_state_->graph().edges();
    std::vector<lien> blocking_links;
    for (const auto& e : edges)
    {
        if (segments_intersect(ext1, ext2,
                               game_state_->portal_pos(e.first),
                               game_state_->portal_pos(e.second)))
            blocking_links.push_back(game_state_->edge_to_link(e));
    }
    return blocking_links;
}

///
// Renvoie un booléen indiquant si la case ``pos`` se trouve dans un champ.
//
bool Api::case_dans_champ(position pos)
{
    // TODO tester

    auto triangles = game_state_->graph().triangles();
    return std::any_of(triangles.cbegin(), triangles.cend(),
                       [this, &pos](const itriple& t) {
                           position a, b, c;
                           game_state_->unpack_triangle_pos(t, a, b, c);
                           return point_in_triangle(a, b, c, pos);
                       });
}

///
// Renvoie la liste des champs dans lesquels la case ``pos`` se trouve. Si la case est un portail, le résultat de ``champs_incidents_portail`` sera inclus dans (mais pas forcément égal à) celui de ``case_champs``.
//
std::vector<champ> Api::case_champs(position pos)
{
    // TODO tester

    auto triangles = game_state_->graph().triangles();
    std::vector<champ> result;
    position a, b, c;
    for (const auto& t : triangles)
    {
        game_state_->unpack_triangle_pos(t, a, b, c);
        if (point_in_triangle(a, b, c, pos))
            result.push_back(game_state_->triangle_to_field(t));
    }
    return result;
}

///
// Renvoie le numéro du joueur correspondant au portail donné, -1 si le portail est neutre, -2 si la case n'est pas un portail. Vous pouvez utiliser cette fonction pour vérifier qu'une case donnée est bien un portail.
//
int Api::portail_joueur(position portail)
{
    // TODO tester

    int portal_id = game_state_->map().portal_id_maybe(portail);
    if (portal_id == -1)
        return -2;
    return game_state_->owner(portal_id);
}

///
// Renvoie le nombre de boucliers présents sur un portail.
//
int Api::portail_boucliers(position portail)
{
    // TODO tester

    int portal_id = game_state_->map().portal_id_maybe(portail);
    if (portal_id == -1)
        return -2; // CHECK do we use this convention

    return game_state_->num_shields(portal_id);
}

///
// Renvoie la liste de tous les liens dont le portail donné est une extrémité.
//
std::vector<lien> Api::liens_incidents_portail(position portail)
{
    // TODO tester

    std::vector<lien> incident_links;

    int portal_id = game_state_->map().portal_id_maybe(portail);
    if (portal_id != -1) // TODO agree on the wanted behavior in that case
    {
        auto& neighbors = game_state_->graph().adj_list()[portal_id];
        for (int v : neighbors)
        {
            auto e = ordered_pair(portal_id, v);
            incident_links.push_back(game_state_->edge_to_link(e));
        }
    }

    return incident_links; // empty if not a portal
}

///
// Renvoie la liste de tous les champs dont le portail donné est un sommet.
//
std::vector<champ> Api::champs_incidents_portail(position portail)
{
    // TODO tester

    std::vector<champ> incident_fields;

    int portal_id = game_state_->map().portal_id_maybe(portail);
    if (portal_id != -1) // TODO agree on the wanted behavior in that case
    {
        auto neighbor_edges = game_state_->graph().incident_triangles(portal_id);
        for (auto& e : neighbor_edges)
        {
            auto t = ordered_triple(portal_id, e.first, e.second);
            incident_fields.push_back(game_state_->triangle_to_field(t));
        }
    }

    return incident_fields; // empty if not a portal
}

///
// Renvoie la liste de tous les champs dont le lien donné est un côté.
//
std::vector<champ> Api::champs_incidents_lien(lien lien)
{
    // TODO tester

    std::vector<champ> incident_fields;

    int u = game_state_->map().portal_id_maybe(lien.extr1);
    int v = game_state_->map().portal_id_maybe(lien.extr2);
    if (u != -1 && v != -1)
    {
        // fix me this line spills over the 80th column :p
        auto third_vertices = game_state_->graph().incident_triangles(std::make_pair(u,v));
        for (int w : third_vertices)
        {
            auto t = ordered_triple(u, v, w);
            incident_fields.push_back(game_state_->triangle_to_field(t));
        }
    }

    return incident_fields; // empty if not a portal

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
// Renvoie la liste des portails détruits par votre adversaire au dernier tour. Cela inclut toutes les utilisations de virus.
//
std::vector<position> Api::hist_portails_detruits()
{
  // TODO
  abort();
}

///
// Renvoie la liste des liens créés par votre adversaire au dernier tour.
//
std::vector<position> Api::hist_liens_crees()
{
  // TODO
  abort();
}

///
// Renvoie la liste des champs créés par votre adversaire au dernier tour.
//
std::vector<position> Api::hist_champs_crees()
{
  // TODO
  abort();
}

///
// Retourne la distance entre deux positions
//
int Api::distance(position pos1, position pos2)
{
    return l1_distance(pos1, pos2);
}

///
// Renvoie le nombre de points que rapporte(rait) chaque tour un champ existant ou hypothétique.
//
int Api::score_triangle(position som1, position som2, position som3)
{
    return (POINTS_CHAMP/2) * abs(determinant(som1, som2, som1, som3));
}

///
// Indique si deux segments se croisent. Cette fonction correspond exactement à la condition d'interférence entre liens, c'est-à-dire qu'elle renvoie ``false`` si l'intersection est une extrémité des deux segments.
//
bool Api::intersection_segments(position a1, position a2, position b1, position b2)
{
    return segments_intersect(a1, a2, b1, b2);
}

///
// Renvoie votre numéro de joueur.
//
int Api::moi()
{
    return player_->id;
}

///
// Renvoie le numéro de votre adversaire.
//
int Api::adversaire()
{
    return game_state_->get_opponent(player_->id);
}

///
// Indique la position de l'agent du joueur désigné par le numéro ``id_joueur``.
//
position Api::position_agent(int id_joueur)
{
    return game_state_->player_pos(id_joueur);
}

///
// Retourne le score du joueur désigné par le numéro ``id_joueur``.
//
int Api::score(int id_joueur)
{
    return game_state_->get_score(id_joueur);
}

///
// Retourne le numéro du tour actuel.
//
int Api::tour_actuel()
{
    return game_state_->get_current_turn();
}

///
// Annule la dernière action. Renvoie ``false`` quand il n'y a pas d'action à annuler ce tour-ci.
//
bool Api::annuler()
{
    // CHECK
    if (!game_state_->can_cancel())
        return false;

    actions_.cancel();
    game_state_ = rules::cancel(game_state_);

    return true;
}

///
// Retourne un dump JSON de l'état complet du jeu.
//
char *Api::get_dump()
{
    if (player_->type != rules::SPECTATOR)
        return NULL;
    return dump_game_state(*game_state_, actions_);
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


