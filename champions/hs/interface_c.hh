///
// This file has been generated, if you wish to
// modify it in a permanent way, please refer
// to the script file : gen/generator_haskell.rb
//

#include <stdbool.h>
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
  PORTAIL_ENNEMI, /* <- Le portail appartient à votre adversaire. */
  LIEN_INTERSECTION, /* <- Le lien croise un lien existant. */
  LIEN_CHAMP, /* <- Le lien se trouve dans un champ existant. */
  LIMITE_BOUCLIERS, /* <- Ce portail est équipé du nombre maximal de boucliers. */
} erreur;


struct position;
struct lien;
struct champ;

typedef struct lien_array {
  struct lien* datas;
  size_t length;
} lien_array;

typedef struct champ_array {
  struct champ* datas;
  size_t length;
} champ_array;

typedef struct position_array {
  struct position* datas;
  size_t length;
} position_array;

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


