{-# LANGUAGE ForeignFunctionInterface #-}

-- This file has been generated, if you wish to
-- modify it in a permanent way, please refer
-- to the script file : gen/generator_haskell.rb

module Prologin where

import Control.Applicative
import Control.Monad
import Data.List
import System.IO.Unsafe
-- import System.Random

import Api

pickRandom :: [a] -> IO a
--pickRandom xs = (xs !!) <$> randomRIO (0, length xs - 1)
pickRandom = return . head

distance_ a b = unsafePerformIO $ distance a b

nbTurbos = nb_points_action `div` (cout_turbo - 1)
deplacement = nb_points_deplacement + nbTurbos * gain_turbo

-- | Fonction appelée au début de la partie
partie_init :: IO ()
partie_init = return () -- no need to init random generator

-- | Fonction appelée à chaque tour
jouer_tour :: IO ()
jouer_tour = do
  portals <- liste_portails
  replicateM_ nbTurbos utiliser_turbo
  let loop = do
        myPos <- position_agent =<< moi
        putStr "my position is "
        print myPos
        movePts <- points_deplacement
        case filter ((<= movePts) . distance_ myPos) . delete myPos $ portals of
          [] -> return ()
          orbit -> do
            randPortal <- pickRandom orbit
            putStrLn $ "moving to " ++ show randPortal
            print =<< deplacer randPortal
            print =<< capturer
            print =<< lier =<< pickRandom portals
            loop
  loop

-- | Fonction appelée à la fin de la partie
partie_fin :: IO ()
partie_fin = return ()


hs_partie_init = partie_init
foreign export ccall hs_partie_init :: IO ()
hs_jouer_tour = jouer_tour
foreign export ccall hs_jouer_tour :: IO ()
hs_partie_fin = partie_fin
foreign export ccall hs_partie_fin :: IO ()
