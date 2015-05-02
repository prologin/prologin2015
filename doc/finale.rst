============================
Finale Prologin 2015 − Sujet
============================

------------
Introduction
------------

Il s'agit d'un jeu basé sur Ingress : deux joueurs, une carte sur laquelle se
trouvent des portails dans des cases. On peut capturer des portails et détruire
les portails des adversaires. Quand on possède deux portails, on peut faire un
lien entre eux deux si aucun lien ne croise le lien potentiel. Le but est de
faire des triangles qui rapportent à chaque tour des points proportionnels à
l'aire du triangle.


Nombre de joueurs
=================

Une partie voit s'affronter 2 joueurs à la fois (bleu et vert).
Chaque joueur possède une base placée dans un coin d'une carte carrée de
dimensions 40 × 40.

TODO


Carte
=====

TODO


But du jeu
==========

TODO


Plateau
=======

Une grille carrée. Le côté du carré est constant (``TAILLE_TERRAIN`` cases).

Des portails sont disposés sur la carte, leur nombre est variable selon la carte
mais leur positions sont fixes et connues des deux joueurs.


Précisions sur la géométrie
===========================

Deux liens [AB] et [CD] interfèrent si [AB] intersecte ]CD[ ou si ]AB[
intersecte [CD], c'est-à-dire que le cas où un point se trouve à l'intérieur
d'un autre segment compte comme une interférence. Cela exclut notamment les
triangles plats. En particulier un segment s'auto-intersecte ce qui interdit de
construire le même lien deux fois, pratique.

D'ailleurs, comme *2 × aire d'un triangle à coordonnées entières* est entier
(comme déterminant de vecteurs entiers) et que la constante de
proportionnalité est paire, les scores obtenus sont toujours entiers.

Un champ correspondra à l'intérieur d'un triangle, au sens topologique,
c'est-à-dire en excluant les côtés.


Mécanismes
==========

Le jeu est tour par tour. Il y a alternance des tours des deux joueurs
(*Turn Based Rules*), et pas de découpage particulier des tours en phases.

* Nombre de joueurs : 2
* Nombre de tours : ``NB_TOURS``

Un joueur peut effectuer des actions qui coûtent des points d'action, sauf pour
les mouvements qui ont une réserve de points spécifique. Aucun des deux types de
points n'est cumulé de tour en tour. Le turbo permet de convertir des points
d'action en points de déplacement ; le contraire est impossible.

* Points de déplacement : ``NB_POINTS_DEPLACEMENT``
* Points d'action : ``NB_POINTS_ACTION``

Pour toute action liée à un portail, le joueur doit se trouver sur la case du
portail. Dans le cas de la création de lien faisant intervenir deux portails à
la fois, le joueur doit se trouver sur l'une des deux extrémités.


Actions
=======

Déplacement
-----------

Le coût d'un déplacement est la distance de Manhattan entre le point de départ
et le point d'arrivée.

Capturer un portail
-------------------

Le joueur peut dépenser ``COUT_CAPTURE`` points d'action pour capturer un portail
neutre.

Relier des portails
-------------------

Le joueur peut dépenser ``COUT_LIEN`` points d'action pour relier le portail à
un autre si le lien n'intersecte aucun autre lien existant et qu'aucun des deux
portails ne se trouve à l'intérieur d'un champ existant. Les deux portails
doivent appartenir au joueur qui crée le lien.

Neutraliser un portail
----------------------

Le joueur peut dépenser ``COUT_NEUTRALISATION`` points d'action pour
neutraliser un portail qui appartient à l'adversaire, celui-ci devient alors
neutre. Si des boucliers (cf. :ref:`ajouter-bouclier`) sont présents sur le
portail, ils augmentent le coup de l'action de
``nombre de boucliers × COUT_NEUTRALISATION_BOUCLIER``.

La neutralisation d'un portail lui fait perdre tous ses boucliers, et fait
disparaître tous les liens reliés à ce portail (ainsi que les triangles donc).

.. _ajouter-bouclier:

Ajouter un bouclier
-------------------

Le joueur peut dépenser ``COUT_BOUCLIER`` points d'action pour incrémenter de
1 le nombre de boucliers sur un portail qu'il contrôle. Un portail neutre n'a
aucun bouclier, un portail qui vient d'être capturé non plus. Le nombre de
boucliers que l'on peut mettre sur un même portail est borné à
``MAX_BOUCLIERS``. Ceci garantit qu'un portail restera toujours destructible
avec les points d'action dont on dispose dans un tour.

Déployer un virus
-----------------

Le joueur peut dépenser ``COUT_VIRUS`` points d'action pour détruire un portail
peu importe son possesseur (supprimant donc les liens, triangles et boucliers
associés) et le changer de propriétaire. Capturer un portail grâce à un virus
ne rapporte pas de points.

Turbo
-----

Le joueur peut, autant de fois qu'il veut par tour, augmenter de ``GAIN_TURBO``
ses points de déplacement pour le tour, en dépensant ``COUT_TURBO`` points
d'actions.


Score
=====

* À chaque capture de portail et à chaque création de lien : le joueur gagne un
  petit nombre de points, respectivement ``POINTS_CREATION_PORTAIL`` et
  ``POINTS_CREATION_LIEN`` points.
* À la fin de chaque tour : le joueur gagne un nombre de points proportionnel à
  l'aire des triangles qu'il contrôle (``POINTS_CHAMP`` points par unité
  d'aire).

Est compté comme un triangle tout triplet de sommets reliés, même si les
triangles se superposent. Les superpositions devront être des inclusions, il n'y
a pas d'intersection possible. Autrement dit, ce qu'on prend sur notre graphe
planaire, ce n'est pas la liste des faces triangulaires, mais celle des
3-cliques.
