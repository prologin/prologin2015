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

#ifndef CONSTANT_HH_
# define CONSTANT_HH_

///
// Taille du terrain (longueur et largeur).
//
# define TAILLE_TERRAIN            30

///
// Nombre de tours à jouer avant la fin de la partie.
//
# define NB_TOURS                  100

///
// Nombre de points de déplacement par tour (avant utilisation du turbo).
//
# define NB_POINTS_DEPLACEMENT     6

///
// Nombre de points d'action par tour.
//
# define NB_POINTS_ACTION          42

///
// Nombre de points d'action que coûte la capture d'un portail.
//
# define COUT_CAPTURE              1

///
// Nombre de points d'action que coûte la création d'un lien.
//
# define COUT_LIEN                 1

///
// Nombre de points d'action que coûte la neutralisation d'un portail de base.
//
# define COUT_NEUTRALISATION       10

///
// Nombre de points d'action supplémentaires que coûte l'attaque pour chaque bouclier présent.
//
# define COUT_NEUTRALISATION_BOUCLIER 4

///
// Nombre de points d'action que coûte la mise en place d'un bouclier.
//
# define COUT_BOUCLIER             2

///
// Nombre de points d'action que coûte l'utilisation d'un turbo.
//
# define COUT_TURBO                6

///
// Nombre maximum de boucliers sur un même portail.
//
# define MAX_BOUCLIERS             4

///
// Nombre de points que rapporte la création d'un portail.
//
# define POINTS_CREATION_PORTAIL   3

///
// Constante de proportionnalité reliant l'aire d'un champ au nombre de points qu'il rapporte par tour.
//
# define POINTS_CHAMP              10

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
  LIEN_DEGENERE, /* <- Les deux extrémités du lien coïncident. */
  LIMITE_BOUCLIERS, /* <- Ce portail est équipé du nombre maximal de boucliers. */
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
  int joueur_l;  /* <- Joueur possédant ce lien. */
} lien;


///
// Représente un champ de contrôle existant.
//
typedef struct champ {
  position som1;  /* <- Premier sommet du champ. */
  position som2;  /* <- Deuxième sommet du champ. */
  position som3;  /* <- Troisième sommet du champ. */
  int joueur_c;  /* <- Joueur possédant ce champ. */
} champ;



#endif // !CONSTANT_HH_
