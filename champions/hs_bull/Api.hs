-- This file has been generated, if you wish to
-- modify it in a permanent way, please refer
-- to the script file : gen/generator_haskell.rb

module Api ( Erreur(..)
           , Position(..)
           , Lien(..)
           , Champ(..)
           , deplacer
           , utiliser_turbo
           , capturer
           , lier
           , neutraliser
           , ajouter_bouclier
           , liste_liens
           , liste_champs
           , liste_portails
           , liens_bloquants
           , lien_existe
           , champ_existe
           , case_dans_champ
           , case_champs
           , portail_joueur
           , portail_boucliers
           , liens_incidents_portail
           , champs_incidents_portail
           , champs_incidents_segment
           , hist_portails_captures
           , hist_portails_neutralises
           , hist_liens_crees
           , hist_champs_crees
           , hist_boucliers_ajoutes
           , distance
           , score_triangle
           , intersection_segments
           , point_dans_triangle
           , moi
           , adversaire
           , position_agent
           , points_action
           , points_deplacement
           , score
           , tour_actuel
           , annuler
           , afficher_erreur
           , afficher_position
           , afficher_lien
           , afficher_champ
           , taille_terrain
           , nb_tours
           , nb_points_deplacement
           , nb_points_action
           , cout_capture
           , cout_lien
           , cout_neutralisation
           , cout_neutralisation_bouclier
           , cout_bouclier
           , cout_turbo
           , max_boucliers
           , points_creation_portail
           , points_champ
           ) where

import CApi

-- | Taille du terrain (longueur et largeur).
taille_terrain  :: Int
taille_terrain = 30
-- | Nombre de tours à jouer avant la fin de la partie.
nb_tours  :: Int
nb_tours = 100
-- | Nombre de points de déplacement par tour (avant utilisation du turbo).
nb_points_deplacement  :: Int
nb_points_deplacement = 6
-- | Nombre de points d'action par tour.
nb_points_action  :: Int
nb_points_action = 42
-- | Nombre de points d'action que coûte la capture d'un portail.
cout_capture  :: Int
cout_capture = 3
-- | Nombre de points d'action que coûte la création d'un lien.
cout_lien  :: Int
cout_lien = 2
-- | Nombre de points d'action que coûte la neutralisation d'un portail de base.
cout_neutralisation  :: Int
cout_neutralisation = 10
-- | Nombre de points d'action supplémentaires que coûte la neutralisation pour chaque bouclier présent.
cout_neutralisation_bouclier  :: Int
cout_neutralisation_bouclier = 5
-- | Nombre de points d'action que coûte la mise en place d'un bouclier sur un portail sans bouclier.
cout_bouclier  :: Int
cout_bouclier = 3
-- | Nombre de points d'action que coûte l'utilisation d'un turbo.
cout_turbo  :: Int
cout_turbo = 6
-- | Nombre maximum de boucliers sur un même portail.
max_boucliers  :: Int
max_boucliers = 6
-- | Nombre de points que rapporte la création d'un portail.
points_creation_portail  :: Int
points_creation_portail = 10
-- | Constante de proportionnalité reliant l'aire d'un champ au nombre de points qu'il rapporte par tour.
points_champ  :: Int
points_champ = 2
