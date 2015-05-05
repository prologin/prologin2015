============================
Finale Prologin 2015 − Sujet
============================

------------
Introduction
------------

Le sujet de la finale de Prologin 2013 est un jeu de stratégie en tour
par tour qui se déroule sur une carte remplie de portails, qui peuvent
être capturés à l'aide d'un agent que les joueurs doivent déplacer sur
la carte. Le but est de recouvrir la surface de la carte avec des
champs triangulaires, formés en reliant les portails capturés entre
eux.


Généralités
===========

Une partie voit s'affronter 2 joueurs (bleu et vert sur l'interface
graphique).

Il y a alternance des tours des deux joueurs, et pas de découpage
particulier des tours en phases. (TODO expliquer mieux)

La condition de victoire est d'avoir un score plus élevé que celui de
son adversaire à la fin de la partie.

-----------
État du jeu
-----------


Carte
=====

La carte consiste en une grille carrée, de ``TAILLE_TERRAIN`` cases de
côté. (La valeur de ``TAILLE_TERRAIN`` est la même pour toutes les
cartes.) Des portails y sont disposés ; leur nombre et leur position
varient selon la carte et restent constants durant toute une
partie. Il en va de même pour les positions de départ des joueurs.


Portails, liens et champs
=========================

Chaque portail peut être soit neutre, soit *contrôlé* (on dira aussi
*possédé*) par l'un des deux joueurs.

Un joueur contrôlant deux portails peut les joindre par un *lien*, qui
se matérialise sur la carte par un segment entre les deux portails. Le
joueur qui contrôle les deux portails aux extrémités est considéré
comme possesseur du lien.

Lorsque trois points sont tous reliés entre eux, l'intérieur du
triangle constitué par ces liens forme un *champ*. Les trois sommets
du champ sont alors forcément contrôlés par le même joueur, dont on
dira qu'il possède le triangle.

Une *interférence* entre deux liens, c'est-à-dire une intersection
entre les deux segments, ne pourra *jamais* se produire et *toute
action devant mener à une telle situation sera interdite par les
règles*. Notez que cette condition est indépendante des possesseurs
des liens.

De plus, la seule façon pour un lien de recontrer l'intérieur d'un
champ sera d'être entierement inclus dans ce champ, qui aura été
construit après le lien.


Précisions sur la géométrie
---------------------------

Deux liens [AB] et [CD] interfèrent si [AB] intersecte ]CD[ ou si ]AB[
intersecte [CD]. Autrement dit, le cas où un point se trouve à
l'intérieur d'un autre segment compte comme une interférence, mais pas
le cas où ils partagent seulement une extrémité (sinon, impossible
d'avoir des triangles !).

Cela exclut notamment la possibilité d'existence de triangles
plats. Notez également qu'un segment s'auto-intersecte ; par
conséquent, il est impossible de relier deux portails deux fois.

Un champ correspond à l'*intérieur* au sens topologique d'un triangle,
c'est-à-dire en excluant les côtés.

Est compté comme un triangle tout triplet de sommets reliés, même si
les triangles se superposent. Les superpositions devront être des
inclusions, il n'y a pas d'intersection possible. Autrement dit, ce
qu'on prend sur notre graphe planaire, ce n'est pas la liste des faces
triangulaires, mais celle des 3-cliques. (TODO: alors lol ce
paragraphe faut vraiment le réécrire)


Agent
=====

Chaque joueur contrôle un agent positionné sur la carte. La position
de l'agent n'est soumise à aucune restriction, si ce n'est de rester à
l'intérieur de la carte : un agent pourra tout autant se trouver sur
un portail, sur une case non-portail, sur une case traversée par un
lien, à l'intérieur d'un champ ou à l'extérieur de tout champ, etc.


---------------------
Déroulement d'un tour
---------------------

Au début de chacun de vos tours, vous vous verrez octroyer
``NB_POINTS_DEPLACEMENT`` *points de déplacement*, et
``NB_POINTS_ACTION`` *points d'action*. Les compteurs des points sont
remis à cette valeur à chaque début de tour (il n'y a pas de cumul de
points sur plusieurs tours), et ne peuvent jamais atteindre une valeur
négative.

Pour consommer ces points, vous pouvez effectuer les actions énumérées
ci-dessous. Vous pouvez jouer autant d'actions que vous voulez durant
un tour, dans n'importe quel ordre, tant que vous avez suffisamment de
points.


Déplacement
===========

Pour déplacer la position de votre agent, vous devez dépenser un
nombre de points de déplacement égal à la distance de Manhattan
(calculée par la fonction ``distance``) entre votre position actuelle
et votre destination. Cela revient à considérer qu'on autorise des
déplacements horizontaux et verticaux d'une case, chacun coûtant un
point de déplacement.


Turbo
-----

Le turbo vous permet de dépenser ``COUT_TURBO`` points d'action pour
gagner un point de déplacement. La réciproque, à savoir convertir des
points de déplacement en points d'action, est impossible.


Actions sur des portails
========================

En règle générale, *pour toute action liée à un portail, votre agent
doit se trouver sur la case du portail*. La création de lien est un
cas particulier puisqu'elle fait intervenir deux portails.


Capturer un portail
-------------------

Vous pouvez dépenser ``COUT_CAPTURE`` points d'action pour capturer un
portail *neutre*.


Relier deux portails
--------------------

Vous pouvez dépenser ``COUT_LIEN`` points d'action pour relier le
portail où votre agent se trouve à un autre quelconque si :

- vous possédez les deux portails ;
- le lien n'interférerait avec aucun autre lien existant ;
- aucun des deux portails ne se trouve à l'intérieur d'un champ
  existant.
 

Neutraliser un portail
----------------------

Vous pouvez dépenser ``COUT_NEUTRALISATION`` points d'action pour
neutraliser un portail qui appartient à l'adversaire, celui-ci devient
alors neutre. Si des boucliers (cf. :ref:`ajouter-bouclier`) sont
présents sur le portail, un coût supplémentaire de ``nombre de
boucliers × COUT_NEUTRALISATION_BOUCLIER`` vient s'ajouter au coût de
base.

La neutralisation d'un portail lui fait perdre tous ses boucliers et
détruit tous les liens reliés à ce portail, et donc également tous les
triangles incidents à ce portail. Il *n'est pas possible* de payer
partiellement pour détruire des boucliers sans entièrement neutraliser
le portail.

.. _ajouter-bouclier:

Ajouter un bouclier
-------------------

Vous pouvez dépenser ``COUT_BOUCLIER`` points d'action pour rajouter
un bouclier sur un portail que vous contrôlez.

Les boucliers sur un portail sont conservés d'un tour à l'autre. Leur
nombre commence à zéro pour un portail qui vient d'être capturé.

Le nombre de boucliers que l'on peut mettre sur un même portail est
borné par ``MAX_BOUCLIERS``. Ceci garantit qu'un portail restera
toujours neutralisable avec les points d'action dont on dispose dans
un tour.


-----
Score
-----

Le score des deux joueurs est initialisé à zéro en début de partie et
ne peut qu'augmenter au cours de la partie. Pour cela, vous pouvez :

* capturer des portails, ce qui incrémente de
  ``POINTS_CREATION_PORTAIL`` votre score ;
* posséder des champs : à la fin de chacun de vos tours, chaque champ
  que vous contrôlez à ce moment vous rapporte un nombre de points
  proportionnel à l'aire qu'il recouvre (``POINTS_CHAMP`` points par
  unité d'aire).


Format de la carte
==================

La carte est représentée sous la forme d'un fichier texte où ``X``
désigne l'emplacement d'un portail et ``.`` une case sans portail.

Le fichier doit suivre le format suivant : ::

  depart_joueur1.x depart_joueur1.y
  depart_joueur2.x depart_joueur2.y
  ASCII map representation

Voici un exemple : ::

  14 14
  15 15
  ..............................
  ..........X........X..........
  ....X.................X.......
  .X................X...........
  .........X................X...
  .............X..........X.....
  ...X.......................X..
  ........X...........X.........
  ...........X.....X............
  .....X.................X......
  ..X..................X........
  ......X.....................X.
  ............X...X.............
  .......X.................X....
  ..............................
  ..............................
  ....X.................X.......
  .............X...X............
  .X.....................X......
  ........X..................X..
  ......X.................X.....
  ............X.....X...........
  .........X...........X........
  ..X.......................X...
  .....X..........X.............
  ...X................X.........
  ...........X................X.
  .......X.................X....
  ..........X........X..........
  ..............................


