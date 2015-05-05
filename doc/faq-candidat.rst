==========================
Finale Prologin 2015 - FAQ
==========================

**Deux trois conseils avant de poser une question**

1. Lire le sujet
2. Relire le sujet
3. Lire votre code
4. Relire votre code
5. Contacter un orga


GUI
===

**Appuyez sur H avant de poser une question !**

Pourquoi la GUI bloque l'exécution de mon programme ?
-----------------------------------------------------

Elle est en mode "pause" par défaut, il faut le désactiver en appuyant sur
Espace ou passer manuellement au tour suivant en appuyant sur N.


Règles
======

Puis-je avoir des précisions sur la géométrie ?
-----------------------------------------------

Deux liens [AB] et [CD] interfèrent si [AB] intersecte ]CD[ ou si ]AB[
intersecte [CD]. Autrement dit, le cas où un point se trouve à
l'intérieur d'un autre segment compte comme une interférence, mais pas
le cas où ils partagent seulement une extrémité (sinon, impossible
d'avoir des champs !).

Cela exclut notamment la possibilité d'existence de champs
plats. Notez également qu'un segment s'auto-intersecte ; par
conséquent, il est impossible de relier deux portails deux fois.

Un champ correspond à l'*intérieur* d'un triangle, c'est-à-dire en
excluant les côtés.

Tous les triangles de la carte sont considérés comme des champs de
contrôle, et pas simplement les faces triangulaires. Cela signifie qu'un
triangle formé par trois triangles adjacents est compté comme un champ
de contrôle supplémentaire, ce qui donne au total 4 champs de contrôle.
