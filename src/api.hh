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

#ifndef API_HH_
#define API_HH_

#include <vector>
#include <rules/game-state.hh>
#include <rules/player.hh>
#include <rules/actions.hh>

#include "game_state.hh"
#include "constant.hh"

/*!
** The methods of this class are exported through 'interface.cc'
** to be called by the clients
*/
class Api
{

public:
    Api(GameState* game_state, rules::Player_sptr player);
    virtual ~Api() { }

    const rules::Player_sptr player() const { return player_; }
    void player_set(rules::Player_sptr player) { player_ = player; }
        
    rules::Actions* actions() { return &actions_; }

    const GameState* game_state() const { return game_state_; }
    GameState* game_state() { return game_state_; }
    void game_state_set(rules::GameState* gs) {
        game_state_ = dynamic_cast<GameState*>(gs);
    }

private:
    GameState* game_state_;
    rules::Player_sptr player_;
    rules::Actions actions_;

public:

///
// Capture le portail où est positionné votre agent.
//
   erreur capturer();
///
// Crée un lien entre le portail où se trouve votre agent et le portail de destination donné en argument.
//
   erreur lier(position portail);
///
// Attaque le portail où se trouve votre agent.
//
   erreur attaquer(int energie);
///
// Déplace votre agent sur la case passée en argument.
//
   erreur deplacer(position dest);
///
// Recharge le portail sur la case passé en argument.
//
   erreur recharger(position portail);
///
// Ajoute un bouclier au portail sur lequel se trouve votre agent.
//
   erreur ajouter_bouclier();
///
// Fait passer le portail où se situe votre agent à l'autre joueur.
//
   erreur utiliser_virus();
///
// Utilise un turbo de vitesse.
//
   erreur utiliser_turbo();
///
// Renvoie la liste de tous les liens présents.
//
   std::vector<lien> liste_liens();
///
// Renvoie la liste de tous les champs de contrôle.
//
   std::vector<champ> liste_champs();
///
// Renvoie la liste de tous les portails de la carte.
//
   std::vector<position> liste_portails();
///
// Renvoie la liste de tous les liens existants qui croisent un segment, entravant la création d'un lien.
//
   std::vector<lien> liens_bloquants(position ext1, position ext2);
///
// Renvoie un booléen indiquant si la case ``pos`` se trouve dans un champ.
//
   bool case_dans_champ(position pos);
///
// Renvoie la liste des champs dans lesquels la case ``pos`` se trouve. Si la case est un portail, le résultat de ``champs_incidents_portail`` sera inclus dans (mais pas forcément égal à) celui de ``case_champs``.
//
   std::vector<champ> case_champs(position pos);
///
// Renvoie le numéro du joueur correspondant au portail donné, -1 si le portail est neutre, -2 si la case n'est pas un portail. Vous pouvez utiliser cette fonction pour vérifier qu'une case donnée est bien un portail.
//
   int portail_joueur(position portail);
///
// Renvoie le nombre de boucliers présents sur un portail.
//
   int portail_boucliers(position portail);
///
// Renvoie la quantité d'énergie restante sur un portail.
//
   int portail_energie(position portail);
///
// Renvoie la liste de tous les liens dont le portail donné est une extrémité.
//
   std::vector<lien> liens_incidents_portail(position portail);
///
// Renvoie la liste de tous les champs dont le portail donné est un sommet.
//
   std::vector<champ> champs_incidents_portail(position portail);
///
// Renvoie la liste de tous les champs dont le lien donné est un côté.
//
   std::vector<champ> champs_incidents_lien(lien lien);
///
// Renvoie la liste des portails capturés par votre adversaire au dernier tour.
//
   std::vector<position> hist_portails_captures();
///
// Renvoie la liste des portails détruits par votre adversaire au dernier tour. Cela inclut toutes les utilisations de virus.
//
   std::vector<position> hist_portails_detruits();
///
// Renvoie la liste des liens créés par votre adversaire au dernier tour.
//
   std::vector<position> hist_liens_crees();
///
// Renvoie la liste des champs créés par votre adversaire au dernier tour.
//
   std::vector<position> hist_champs_crees();
///
// Renvoie votre numéro de joueur.
//
   int moi();
///
// Renvoie le numéro de votre adversaire.
//
   int adversaire();
///
// Indique la position de l'agent du joueur désigné par le numéro ``id_joueur``.
//
   position position_agent(int id_joueur);
///
// Retourne la distance entre deux positions
//
   int distance(position pos1, position pos2);
///
// Retourne le score du joueur désigné par le numéro ``id_joueur``.
//
   int score(int id_joueur);
///
// Retourne le numéro du tour actuel.
//
   int tour_actuel();
///
// Annule la dernière action. Renvoie ``false`` quand il n'y a pas d'action à annuler ce tour-ci.
//
   bool annuler();
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

};


#endif /* !API_HH_ */
