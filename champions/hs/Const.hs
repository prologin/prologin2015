-- This file has been generated, if you wish to
-- modify it in a permanent way, please refer
-- to the script file : gen/generator_haskell.rb

module Const where

-- Taille du terrain (longueur et largeur)
taille_terrain :: Int
taille_terrain = 40

-- Nombre de tours à jouer avant la fin de la partie
nb_tours :: Int
nb_tours = 100

-- Nombre de points de déplacements par tour
nb_points_deplacement :: Int
nb_points_deplacement = 8

-- Nombre de points d'action à chaque tour
nb_points_action :: Int
nb_points_action = 200

-- Nombre de points d'actions que coûte la capture d'un portail
cout_capture :: Int
cout_capture = 5

-- Nombre de points d'actions que coûte la création d'un lien
cout_lien :: Int
cout_lien = 5

-- Nombre de points d'actions que coûte la neutralisation d'un portail de base.
cout_neutralisation :: Int
cout_neutralisation = 50

-- Nombre de points d'actions supplémentaires que coûte l'attaque pour chaque bouclier présent.
cout_neutralisation_bouclier :: Int
cout_neutralisation_bouclier = 20

-- Nombre de points d'actions que coûte la mise en place d'un bouclier.
cout_bouclier :: Int
cout_bouclier = 10

-- Nombre de points d'actions que coûte l'utilisation d'un virus
cout_virus :: Int
cout_virus = 100

-- Nombre de points d'actions que coûte un turbo
cout_turbo :: Int
cout_turbo = 10

-- Nombre de points de déplacement donnés par le turbo
gain_turbo :: Int
gain_turbo = 1

-- Nombre maximum de boucliers sur un même portail.
max_boucliers :: Int
max_boucliers = 4

-- Nombre de points que rapporte la création d'un portail.
points_creation_portail :: Int
points_creation_portail = 3

-- Nombre de points que rapporte la création d'un lien.
points_creation_lien :: Int
points_creation_lien = 5

-- Constante de proportionnalité reliant l'aire d'un champ au nombre de points qu'il rapporte par tour.
points_champ :: Int
points_champ = 10

