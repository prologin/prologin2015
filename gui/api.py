# -*- coding: iso-8859-1 -*-

# This file is copied from the "api.py" that is generated for usual champions.
# For the GUI, all we need is a few constants so don't bother with making the
# rest of the API work:
#
#   from _api import *

# Taille du terrain (longueur et largeur)
TAILLE_TERRAIN = 40

# Nombre de tours à jouer avant la fin de la partie
NB_TOURS = 100

# Nombre de points de déplacements par tour
NB_POINTS_DEPLACEMENT = 8

# Nombre de points d'action à chaque tour
NB_POINTS_ACTION = 200

# Nombre de points d'actions que coûte la capture d'un portail
COUT_CAPTURE = 5

# Nombre de points d'actions que coûte la création d'un lien
COUT_LIEN = 5

# Nombre de points d'actions que coûte la destruction d'un portail de base.
COUT_DESTRUCTION = 50

# Nombre de points d'actions supplémentaires que coûte l'attaque pour chaque bouclier présent.
COUT_DESTRUCTION_BOUCLIER = 20

# Nombre de points d'actions que coûte la mise en place d'un bouclier.
COUT_BOUCLIER = 10

# Nombre de points d'actions que coûte l'utilisation d'un virus
COUT_VIRUS = 100

# Nombre de points d'actions que coûte un turbo
COUT_TURBO = 10

# Nombre de points de déplacement donnés par le turbo
GAIN_TURBO = 1

# Nombre maximum de boucliers sur un même portail.
MAX_BOUCLIERS = 4

# Nombre de points que rapporte la création d'un portail.
POINTS_CREATION_PORTAIL = 3

# Nombre de points que rapporte la création d'un lien.
POINTS_CREATION_LIEN = 5

# Constante de proportionnalité reliant l'aire d'un champ au nombre de points qu'il rapporte par tour.
POINTS_CHAMP = 10


from enum import IntEnum

# Erreurs possibles
class erreur(IntEnum):
    OK = 0  # <- L'action a été exécutée avec succès
    PA_INSUFFISANTS = 1  # <- Vous ne possédez pas assez de points d'action pour cette action.
    AUCUN_PORTAIL = 2  # <- La position spécifiée n'est pas un portail.
    POSITION_INVALIDE = 3  # <- La position spécifiée est hors de la carte.
    POSITION_ELOIGNEE = 4  # <- La destination est trop éloignée.
    PORTAIL_AMI = 5  # <- Le portail vous appartient.
    PORTAIL_NEUTRE = 6  # <- Le portail est neutre.
    PORTAIL_ENNEMI = 7  # <- Le portail ne vous appartient pas.
    LIEN_INTERSECTION = 8  # <- Le lien croise un lien existant.
    LIEN_CHAMP = 9  # <- Le lien se trouve dans un champ existant.
    LIMITE_BOUCLIERS = 10  # <- Ce portail est équipé du nombre maximal de boucliers.
    VALEUR_INVALIDE = 11  # <- La valeur donnée est invalide.


from collections import namedtuple

# Position sur la carte, donnée par deux coordonnées.

# Représente un lien existant.
lien = namedtuple("lien",
    'extr1 ' # <- Première extrémité du lien.
    'extr2 ' # <- Seconde extrémité du lien.
    'joueur ' # <- Joueur possédant ce lien.
)


# Représente un champ de contrôle existant.
champ = namedtuple("champ",
    'som1 ' # <- Premier sommet du champ.
    'som2 ' # <- Deuxième sommet du champ.
    'som3 ' # <- Troisième sommet du champ.
    'joueur ' # <- Joueur possédant ce champ.
)


