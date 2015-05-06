{-# LANGUAGE ForeignFunctionInterface #-}

module Prologin where

import Api
import Control.Arrow ((&&&))
import Control.Monad (filterM, replicateM_)

instance Ord Position where
  (Position x1 y1) <= (Position x2 y2) = (x1, y1) <= (x2, y2)

partie_init :: IO ()
partie_init = return ()

jouer_tour :: IO ()
jouer_tour = do
  id <- moi
  position <- position_agent id
  notMine <- filterM (fmap (/= id) . portail_joueur) =<< liste_portails
  let target = closest position notMine
  let off = distance' position target - nb_points_deplacement
  replicateM_ off utiliser_turbo
  deplacer target
  neutraliser
  capturer
  mapM_ lier =<< filterM (fmap (== id) . portail_joueur) =<< liste_portails
  replicateM_ max_boucliers ajouter_bouclier

partie_fin :: IO ()
partie_fin = return ()


-- | Return Manhattan distance between two positions
distance' :: Position -> Position -> Int
distance' (Position x1 y1) (Position x2 y2) = abs (x1 - x2) + abs (y1 - y2)

-- | Find closest postition of current position
closest :: Position -> [Position] -> Position
closest me = snd . minimum . map (distance' me &&& id)

hs_partie_init = partie_init
foreign export ccall hs_partie_init :: IO ()
hs_jouer_tour = jouer_tour
foreign export ccall hs_jouer_tour :: IO ()
hs_partie_fin = partie_fin
foreign export ccall hs_partie_fin :: IO ()
