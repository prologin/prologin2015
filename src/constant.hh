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
// Taille du terrain (longueur et largeur)
//
# define TAILLE_TERRAIN            40

///
// Nombre de tours à jouer avant la fin de la partie
//
# define NB_TOURS                  100

///
// Nombre de points de déplacements par tour
//
# define NB_POINTS_DEPLACEMENT     8

///
// Nombre de points d'action à chaque tour
//
# define NB_POINTS_ACTION          200

///
// Nombre de points d'actions que coûte la capture d'un portail
//
# define COUT_CAPTURE              5

///
// Nombre de points d'actions que coûte la création d'un lien
//
# define COUT_LIEN                 5

///
// Nombre de points d'actions que coûte la neutralisation d'un portail de base.
//
# define COUT_NEUTRALISATION       50

///
// Nombre de points d'actions supplémentaires que coûte l'attaque pour chaque bouclier présent.
//
# define COUT_NEUTRALISATION_BOUCLIER 20

///
// Nombre de points d'actions que coûte la mise en place d'un bouclier.
//
# define COUT_BOUCLIER             10

///
// Nombre de points d'actions que coûte l'utilisation d'un virus
//
# define COUT_VIRUS                100

///
// Nombre de points d'actions que coûte un turbo
//
# define COUT_TURBO                10

///
// Nombre de points de déplacement donnés par le turbo
//
# define GAIN_TURBO                1

///
// Nombre maximum de boucliers sur un même portail.
//
# define MAX_BOUCLIERS             4

///
// Nombre de points que rapporte la création d'un portail.
//
# define POINTS_CREATION_PORTAIL   3

///
// Nombre de points que rapporte la création d'un lien.
//
# define POINTS_CREATION_LIEN      5

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



#endif // !CONSTANT_HH_
