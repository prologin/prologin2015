{-# LANGUAGE ForeignFunctionInterface #-}

-- This file has been generated, if you wish to
-- modify it in a permanent way, please refer
-- to the script file : gen/generator_haskell.rb

module Prologin where

import Api


-- | Fonction appelée au début de la partie
partie_init :: IO ()
partie_init = return () -- A completer

-- | Fonction appelée à chaque tour
jouer_tour :: IO ()
jouer_tour = return () -- A completer

-- | Fonction appelée à la fin de la partie
partie_fin :: IO ()
partie_fin = return () -- A completer


hs_partie_init = partie_init
foreign export ccall hs_partie_init :: IO ()
hs_jouer_tour = jouer_tour
foreign export ccall hs_jouer_tour :: IO ()
hs_partie_fin = partie_fin
foreign export ccall hs_partie_fin :: IO ()
