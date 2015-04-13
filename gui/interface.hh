///
// This file has been generated, if you wish to
// modify it in a permanent way, please refer
// to the script file : gen/generator_python.rb
//

#ifndef INTERFACE_HH_
# define INTERFACE_HH_

# include <Python.h>
# include <vector>
# include <string>

///
// Erreurs possibles
//
typedef enum erreur {
  OK, /* <- L'action a été exécutée avec succès */
  PA_INSUFFISANTS, /* <- Vous ne possédez pas assez de points d'action pour cette action. */
  AUCUN_PORTAIL, /* <- La position spécifiée n'est pas un portail. */
  POSITION_INVALIDE, /* <- La position spécifiée est hors de la carte. */
  POSITION_ELOIGNEE, /* <- La destination est trop éloignée. */
  PORTAIL_AMI, /* <- Le portail vous appartient. */
  PORTAIL_NEUTRE, /* <- Le portail est neutre. */
  PORTAIL_ENNEMI, /* <- Le portail ne vous appartient pas. */
  LIEN_INTERSECTION, /* <- Le lien croise un lien existant. */
  LIEN_CHAMP, /* <- Le lien se trouve dans un champ existant. */
  LIMITE_BOUCLIERS, /* <- Ce portail est équipé du nombre maximal de boucliers. */
  VALEUR_INVALIDE, /* <- La valeur donnée est invalide. */
} erreur;


///
// Position sur la carte, donnée par deux coordonnées.
//
typedef struct position {
  int x;  /* <- Coordonnée en X */
  int y;  /* <- Coordonnée en Y */
} position;


///
// Représente un lien existant.
//
typedef struct lien {
  position extr1;  /* <- Première extrémité du lien. */
  position extr2;  /* <- Seconde extrémité du lien. */
  int joueur;  /* <- Joueur possédant ce lien. */
} lien;


///
// Représente un champ de contrôle existant.
//
typedef struct champ {
  position som1;  /* <- Premier sommet du champ. */
  position som2;  /* <- Deuxième sommet du champ. */
  position som3;  /* <- Troisième sommet du champ. */
  int joueur;  /* <- Joueur possédant ce champ. */
} champ;



extern "C" {

///
// Capture le portail où est positionné votre agent.
//
erreur api_capturer();

///
// Crée un lien entre le portail où se trouve votre agent et le portail de destination donné en argument.
//
erreur api_lier(position portail);

///
// Détruit le portail où se trouve votre agent.
//
erreur api_detruire();

///
// Déplace votre agent sur la case passée en argument.
//
erreur api_deplacer(position dest);

///
// Ajoute un bouclier au portail sur lequel se trouve votre agent.
//
erreur api_ajouter_bouclier();

///
// Fait passer le portail où se situe votre agent à l'autre joueur.
//
erreur api_utiliser_virus();

///
// Utilise un turbo.
//
erreur api_utiliser_turbo();

///
// Renvoie la liste de tous les liens présents.
//
std::vector<lien> api_liste_liens();

///
// Renvoie la liste de tous les champs de contrôle.
//
std::vector<champ> api_liste_champs();

///
// Renvoie la liste de tous les portails de la carte.
//
std::vector<position> api_liste_portails();

///
// Renvoie la liste de tous les liens existants qui croisent un segment, entravant la création d'un lien.
//
std::vector<lien> api_liens_bloquants(position ext1, position ext2);

///
// Renvoie un booléen indiquant si la case ``pos`` se trouve dans un champ.
//
bool api_case_dans_champ(position pos);

///
// Renvoie la liste des champs dans lesquels la case ``pos`` se trouve. Si la case est un portail, le résultat de ``champs_incidents_portail`` sera inclus dans (mais pas forcément égal à) celui de ``case_champs``.
//
std::vector<champ> api_case_champs(position pos);

///
// Renvoie le numéro du joueur correspondant au portail donné, -1 si le portail est neutre, -2 si la case n'est pas un portail. Vous pouvez utiliser cette fonction pour vérifier qu'une case donnée est bien un portail.
//
int api_portail_joueur(position portail);

///
// Renvoie le nombre de boucliers présents sur un portail.
//
int api_portail_boucliers(position portail);

///
// Renvoie la liste de tous les liens dont le portail donné est une extrémité.
//
std::vector<lien> api_liens_incidents_portail(position portail);

///
// Renvoie la liste de tous les champs dont le portail donné est un sommet.
//
std::vector<champ> api_champs_incidents_portail(position portail);

///
// Renvoie la liste de tous les champs dont le lien donné est un côté.
//
std::vector<champ> api_champs_incidents_lien(lien lien);

///
// Renvoie la liste des portails capturés par votre adversaire au dernier tour.
//
std::vector<position> api_hist_portails_captures();

///
// Renvoie la liste des portails détruits par votre adversaire au dernier tour. Cela inclut toutes les utilisations de virus.
//
std::vector<position> api_hist_portails_detruits();

///
// Renvoie la liste des liens créés par votre adversaire au dernier tour.
//
std::vector<position> api_hist_liens_crees();

///
// Renvoie la liste des champs créés par votre adversaire au dernier tour.
//
std::vector<position> api_hist_champs_crees();

///
// Retourne la distance entre deux positions
//
int api_distance(position pos1, position pos2);

///
// Renvoie le nombre de points que rapporte(rait) chaque tour un champ existant ou hypothétique.
//
int api_score_triangle(position som1, position som2, position som3);

///
// Indique si deux segments se croisent. Cette fonction correspond exactement à la condition d'interférence entre liens, c'est-à-dire qu'elle renvoie ``false`` si l'intersection est une extrémité des deux segments.
//
bool api_intersection_segments(position a1, position a2, position b1, position b2);

///
// Renvoie votre numéro de joueur.
//
int api_moi();

///
// Renvoie le numéro de votre adversaire.
//
int api_adversaire();

///
// Indique la position de l'agent du joueur désigné par le numéro ``id_joueur``.
//
position api_position_agent(int id_joueur);

///
// Retourne le score du joueur désigné par le numéro ``id_joueur``.
//
int api_score(int id_joueur);

///
// Retourne le numéro du tour actuel.
//
int api_tour_actuel();

///
// Annule la dernière action. Renvoie ``false`` quand il n'y a pas d'action à annuler ce tour-ci.
//
bool api_annuler();

///
// Affiche le contenu d'une valeur de type erreur
//
void api_afficher_erreur(erreur v);

///
// Affiche le contenu d'une valeur de type position
//
void api_afficher_position(position v);

///
// Affiche le contenu d'une valeur de type lien
//
void api_afficher_lien(lien v);

///
// Affiche le contenu d'une valeur de type champ
//
void api_afficher_champ(champ v);

}

#endif // !INTERFACE_HH_