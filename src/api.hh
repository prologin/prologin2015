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

#include <rules/actions.hh>
#include <rules/api.hh>
#include <rules/game-state.hh>
#include <rules/player.hh>
#include <vector>

#include "actions.hh"
#include "constant.hh"
#include "game_state.hh"

/*!
** The methods of this class are exported through 'interface.cc'
** to be called by the clients
*/
class Api final : public rules::Api<GameState, erreur>
{
public:
    Api(std::unique_ptr<GameState> game_state,
        std::shared_ptr<rules::Player> player);

    ///
    // Déplace votre agent sur la case passée en argument.
    //
    ApiActionFunc<ActionDeplacer> deplacer{this};
    ///
    // Utilise un turbo.
    //
    ApiActionFunc<ActionUtiliserTurbo> utiliser_turbo{this};
    ///
    // Capture le portail où est positionné votre agent.
    //
    ApiActionFunc<ActionCapturer> capturer{this};
    ///
    // Crée un lien entre le portail où se trouve votre agent et le portail de
    // destination donné en argument.
    //
    ApiActionFunc<ActionLier> lier{this};
    ///
    // Neutralise le portail où se trouve votre agent.
    //
    ApiActionFunc<ActionNeutraliser> neutraliser{this};
    ///
    // Ajoute un bouclier au portail sur lequel se trouve votre agent.
    //
    ApiActionFunc<ActionAjouterBouclier> ajouter_bouclier{this};
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
    // Renvoie la liste de tous les liens existants qui croisent un segment,
    // entravant la création d'un lien.
    //
    std::vector<lien> liens_bloquants(position ext1, position ext2);
    ///
    // Prend les positions de deux portails, et renvoie un booléen indiquant
    // s'ils sont reliés. Le résultat est `false` lorsque l'une des deux
    // positions ne repère pas un portail.
    //
    bool lien_existe(position ext1, position ext2);
    ///
    // Renvoie un booléen indiquant si les 3 positions repèrent bien 3 portails
    // tous reliés entre eux.
    //
    bool champ_existe(position som1, position som2, position som3);
    ///
    // Renvoie un booléen indiquant si la case ``pos`` se trouve dans un champ.
    //
    bool case_dans_champ(position pos);
    ///
    // Renvoie la liste des champs à l'intérieur desquels ``pos`` se trouve. Si
    // la case est un portail, le résultat de ``case_champs`` sera disjoint de
    // celui de ``champs_incidents_portail``.
    //
    std::vector<champ> case_champs(position pos);
    ///
    // Renvoie le numéro du joueur correspondant au portail donné, -1 si le
    // portail est neutre, -2 si la case n'est pas un portail. Vous pouvez
    // utiliser cette fonction pour vérifier qu'une case donnée est bien un
    // portail.
    //
    int portail_joueur(position portail);
    ///
    // Renvoie le nombre de boucliers présents sur un portail (-2 si la case
    // n'est pas un portail).
    //
    int portail_boucliers(position portail);
    ///
    // Renvoie la liste de tous les liens dont le portail donné est une
    // extrémité.
    //
    std::vector<lien> liens_incidents_portail(position portail);
    ///
    // Renvoie la liste de tous les champs dont le portail donné est un sommet.
    //
    std::vector<champ> champs_incidents_portail(position portail);
    ///
    // Renvoie la liste de tous les champs dont le lien donné est un côté. Si le
    // segment n'est pas un lien présent, renvoie la liste de tous les champs
    // que la création du lien ferait apparaître.
    //
    std::vector<champ> champs_incidents_segment(position ext1, position ext2);
    ///
    // Renvoie la liste des portails capturés par votre adversaire au dernier
    // tour.
    //
    std::vector<position> hist_portails_captures();
    ///
    // Renvoie la liste des portails neutralisés par votre adversaire au dernier
    // tour. Cela inclut toutes les utilisations de virus.
    //
    std::vector<position> hist_portails_neutralises();
    ///
    // Renvoie la liste des liens créés par votre adversaire au dernier tour.
    //
    std::vector<lien> hist_liens_crees();
    ///
    // Renvoie la liste des champs créés par votre adversaire au dernier tour.
    //
    std::vector<champ> hist_champs_crees();
    ///
    // Renvoie la liste des positions où votre adversaire a ajouté des boucliers
    // au dernier tour.
    //
    std::vector<position> hist_boucliers_ajoutes();
    ///
    // Renvoie la distance de Manhattan entre deux positions.
    //
    int distance(position pos1, position pos2);
    ///
    // Renvoie le nombre de points que rapporte(rait) chaque tour un champ
    // existant ou hypothétique.
    //
    int score_triangle(position som1, position som2, position som3);
    ///
    // Indique si deux segments se croisent. Cette fonction correspond
    // exactement à la condition d'interférence entre liens, c'est-à-dire
    // qu'elle renvoie ``false`` si l'intersection est une extrémité des deux
    // segments.
    //
    bool intersection_segments(position a1, position a2, position b1,
                               position b2);
    ///
    // Indique si un point se trouve à l'intérieur d'un triangle. Le critère
    // coïncide avec celui de ``case_champs``.
    //
    bool point_dans_triangle(position p, position som1, position som2,
                             position som3);
    ///
    // Renvoie votre numéro de joueur.
    //
    int moi();
    ///
    // Renvoie le numéro de votre adversaire.
    //
    int adversaire();
    ///
    // Indique la position de l'agent du joueur désigné par le numéro
    // ``id_joueur``.
    //
    position position_agent(int id_joueur);
    ///
    // Indique votre nombre de points d'actions restants pour ce tour-ci.
    //
    int points_action();
    ///
    // Indique votre nombre de points de déplacement restants pour ce tour-ci.
    //
    int points_deplacement();
    ///
    // Renvoie le score du joueur désigné par le numéro ``id_joueur``.
    //
    int score(int id_joueur);
    ///
    // Renvoie le numéro du tour actuel.
    //
    int tour_actuel();
    ///
    // Annule la dernière action. Renvoie ``false`` quand il n'y a pas d'action
    // à annuler ce tour-ci.
    //
    bool annuler();
    ///
    // Retourne un dump JSON de l'état complet du jeu.
    //
    char* get_dump();
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
