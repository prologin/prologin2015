///
// This file has been generated, if you wish to
// modify it in a permanent way, please refer
// to the script file : gen/generator_haskell.rb
//

#include <vector>
#include <string>
#include <stdlib.h>
#include "interface_c.hh"
typedef struct __internal__cxx__position {
  int x;
  int y;
} __internal__cxx__position;
typedef struct __internal__cxx__lien {
  __internal__cxx__position extr1;
  __internal__cxx__position extr2;
  int joueur_l;
} __internal__cxx__lien;
typedef struct __internal__cxx__champ {
  __internal__cxx__position som1;
  __internal__cxx__position som2;
  __internal__cxx__position som3;
  int joueur_c;
} __internal__cxx__champ;
extern "C" erreur api_capturer(void);
extern "C" erreur api_lier(__internal__cxx__position portail);
extern "C" erreur api_neutraliser(void);
extern "C" erreur api_deplacer(__internal__cxx__position dest);
extern "C" erreur api_ajouter_bouclier(void);
extern "C" erreur api_utiliser_virus(void);
extern "C" erreur api_utiliser_turbo(void);
extern "C" std::vector<__internal__cxx__lien> api_liste_liens(void);
extern "C" std::vector<__internal__cxx__champ> api_liste_champs(void);
extern "C" std::vector<__internal__cxx__position> api_liste_portails(void);
extern "C" std::vector<__internal__cxx__lien> api_liens_bloquants(__internal__cxx__position ext1, __internal__cxx__position ext2);
extern "C" bool api_lien_existe(__internal__cxx__position ext1, __internal__cxx__position ext2);
extern "C" bool api_champ_existe(__internal__cxx__position som1, __internal__cxx__position som2, __internal__cxx__position som3);
extern "C" bool api_case_dans_champ(__internal__cxx__position pos);
extern "C" std::vector<__internal__cxx__champ> api_case_champs(__internal__cxx__position pos);
extern "C" int api_portail_joueur(__internal__cxx__position portail);
extern "C" int api_portail_boucliers(__internal__cxx__position portail);
extern "C" std::vector<__internal__cxx__lien> api_liens_incidents_portail(__internal__cxx__position portail);
extern "C" std::vector<__internal__cxx__champ> api_champs_incidents_portail(__internal__cxx__position portail);
extern "C" std::vector<__internal__cxx__champ> api_champs_incidents_segment(__internal__cxx__position ext1, __internal__cxx__position ext2);
extern "C" std::vector<__internal__cxx__position> api_hist_portails_captures(void);
extern "C" std::vector<__internal__cxx__position> api_hist_portails_neutralises(void);
extern "C" std::vector<__internal__cxx__position> api_hist_liens_crees(void);
extern "C" std::vector<__internal__cxx__position> api_hist_champs_crees(void);
extern "C" int api_distance(__internal__cxx__position pos1, __internal__cxx__position pos2);
extern "C" int api_score_triangle(__internal__cxx__position som1, __internal__cxx__position som2, __internal__cxx__position som3);
extern "C" bool api_intersection_segments(__internal__cxx__position a1, __internal__cxx__position a2, __internal__cxx__position b1, __internal__cxx__position b2);
extern "C" int api_moi(void);
extern "C" int api_adversaire(void);
extern "C" __internal__cxx__position api_position_agent(int id_joueur);
extern "C" int api_score(int id_joueur);
extern "C" int api_tour_actuel(void);
extern "C" bool api_annuler(void);
extern "C" void api_afficher_erreur(erreur v);
extern "C" void api_afficher_position(__internal__cxx__position v);
extern "C" void api_afficher_lien(__internal__cxx__lien v);
extern "C" void api_afficher_champ(__internal__cxx__champ v);
extern "C" void partie_init();
extern "C" void jouer_tour();
extern "C" void partie_fin();
