{-# LANGUAGE ForeignFunctionInterface #-}
{-# LANGUAGE TypeFamilies #-}
{-# LANGUAGE FlexibleInstances #-}
{-# LANGUAGE UndecidableInstances #-}

{-# OPTIONS_HADDOCK hide #-}

-- This file has been generated, if you wish to
-- modify it in a permanent way, please refer
-- to the script file : gen/generator_haskell.rb

module CApi where

import Data.List (foldl')
import Foreign
import Foreign.C.Types

import Foreign.Marshal.Array

#include "interface_c.hh"
type CBool = CChar

class ApiStorable a where
  type ApiStorableType a
  toStorable :: a -> (ApiStorableType a -> IO b) -> IO b
  unStorable :: ApiStorableType a -> IO a
  type ApiStorableBaseType a
  toStorableBase :: a -> (ApiStorableBaseType a -> IO b) -> IO b
  unStorableBase :: ApiStorableBaseType a -> IO a

instance ApiStorable () where
  type ApiStorableType () = ()
  toStorable () f = f ()
  {-# INLINE toStorable #-}
  unStorable _ = return ()
  {-# INLINE unStorable #-}
  type ApiStorableBaseType () = ()
  toStorableBase = toStorable
  {-# INLINE toStorableBase #-}
  unStorableBase = unStorable
  {-# INLINE unStorableBase #-}
instance ApiStorable Int where
  type ApiStorableType Int = CInt
  toStorable x f = f (fromIntegral x)
  {-# INLINE toStorable #-}
  unStorable = return . fromIntegral
  {-# INLINE unStorable #-}
  type ApiStorableBaseType Int = ApiStorableType Int
  toStorableBase = toStorable
  {-# INLINE toStorableBase #-}
  unStorableBase = unStorable
  {-# INLINE unStorableBase #-}
instance ApiStorable Bool where
  type ApiStorableType Bool = CBool
  toStorable x f = f ((\bx -> if bx then 1 else 0) x)
  {-# INLINE toStorable #-}
  unStorable = return . (/= 0)
  {-# INLINE unStorable #-}
  type ApiStorableBaseType Bool = ApiStorableType Bool
  toStorableBase = toStorable
  {-# INLINE toStorableBase #-}
  unStorableBase = unStorable
  {-# INLINE unStorableBase #-}
-- | Erreurs possibles
data Erreur =
    Ok -- ^ L'action a été exécutée avec succès 
  | Pa_insuffisants -- ^ Vous ne possédez pas assez de points d'action pour cette action. 
  | Aucun_portail -- ^ La position spécifiée n'est pas un portail. 
  | Position_invalide -- ^ La position spécifiée est hors de la carte. 
  | Position_eloignee -- ^ La destination est trop éloignée. 
  | Portail_ami -- ^ Le portail vous appartient. 
  | Portail_neutre -- ^ Le portail est neutre. 
  | Portail_ennemi -- ^ Le portail appartient à votre adversaire. 
  | Lien_intersection -- ^ Le lien croise un lien existant. 
  | Lien_champ -- ^ Le lien se trouve dans un champ existant. 
  | Lien_degenere -- ^ Les deux extrémités du lien coïncident. 
  | Limite_boucliers -- ^ Ce portail est équipé du nombre maximal de boucliers. 
  deriving(Show, Eq, Enum)
type CErreur = CInt

instance ApiStorable Erreur where
  type ApiStorableType Erreur = CInt
  toStorable x f = f (fromIntegral (fromEnum x))
  {-# INLINE toStorable #-}
  unStorable = return . toEnum . fromIntegral
  {-# INLINE unStorable #-}
  type ApiStorableBaseType Erreur = ApiStorableType Erreur
  toStorableBase = toStorable
  {-# INLINE toStorableBase #-}
  unStorableBase = unStorable
  {-# INLINE unStorableBase #-}
-- | Position sur la carte, donnée par deux coordonnées.
data Position = Position Int Int
  deriving(Show, Eq)
data CPosition = CPosition CInt CInt
instance Storable CPosition where
  sizeOf    _ = (#size position)
  {-# INLINE sizeOf #-}
  alignment _ = alignment (undefined :: CInt)
  {-# INLINE alignment #-}
  peek ptr = do
    ax <- (#peek position, x) ptr
    ay <- (#peek position, y) ptr
    return $ CPosition ax ay
  {-# INLINE peek #-}
  poke ptr (CPosition ax ay) = do
    (#poke position, x) ptr ax
    (#poke position, y) ptr ay
  {-# INLINE poke #-}
instance ApiStorable Position where
  type ApiStorableType Position = Ptr CPosition
  toStorable (Position ax ay) f = toStorableBase ax $ \ax' ->  toStorableBase ay $ \ay' ->  do
    alloca $ \ptr -> do
      poke ptr $ CPosition ax' ay'
      f ptr
  {-# INLINE toStorable #-}
  unStorable ptr = do
    (CPosition ax' ay') <- peek ptr
    ax <- unStorableBase ax'
    ay <- unStorableBase ay'
    return $ Position ax ay
  {-# INLINE unStorable #-}
  type ApiStorableBaseType Position = CPosition
  toStorableBase (Position ax ay) f =
    toStorableBase ax $ \ax' ->  toStorableBase ay $ \ay' ->  f (CPosition ax' ay')
  {-# INLINE toStorableBase #-}
  unStorableBase (CPosition ax' ay') = do
    ax <- unStorableBase ax'
    ay <- unStorableBase ay'
    return $ Position ax ay
  {-# INLINE unStorableBase #-}
-- | Représente un lien existant.
data Lien = Lien {
      extr1 :: Position -- ^ Première extrémité du lien.
  ,   extr2 :: Position -- ^ Seconde extrémité du lien.
  ,   joueur_l :: Int -- ^ Joueur possédant ce lien.
}
  deriving(Show, Eq)
data CLien = CLien {
      cextr1 :: CPosition -- ^ Première extrémité du lien.
  ,   cextr2 :: CPosition -- ^ Seconde extrémité du lien.
  ,   cjoueur_l :: CInt -- ^ Joueur possédant ce lien.
}
instance Storable CLien where
  sizeOf    _ = (#size lien)
  {-# INLINE sizeOf #-}
  alignment _ = alignment (undefined :: CInt)
  {-# INLINE alignment #-}
  peek ptr = do
    aextr1 <- (#peek lien, extr1) ptr
    aextr2 <- (#peek lien, extr2) ptr
    ajoueur_l <- (#peek lien, joueur_l) ptr
    return $ CLien aextr1 aextr2 ajoueur_l
  {-# INLINE peek #-}
  poke ptr (CLien aextr1 aextr2 ajoueur_l) = do
    (#poke lien, extr1) ptr aextr1
    (#poke lien, extr2) ptr aextr2
    (#poke lien, joueur_l) ptr ajoueur_l
  {-# INLINE poke #-}
instance ApiStorable Lien where
  type ApiStorableType Lien = Ptr CLien
  toStorable (Lien aextr1 aextr2 ajoueur_l) f = toStorableBase aextr1 $ \aextr1' ->  toStorableBase aextr2 $ \aextr2' ->  toStorableBase ajoueur_l $ \ajoueur_l' ->  do
    alloca $ \ptr -> do
      poke ptr $ CLien aextr1' aextr2' ajoueur_l'
      f ptr
  {-# INLINE toStorable #-}
  unStorable ptr = do
    (CLien aextr1' aextr2' ajoueur_l') <- peek ptr
    aextr1 <- unStorableBase aextr1'
    aextr2 <- unStorableBase aextr2'
    ajoueur_l <- unStorableBase ajoueur_l'
    return $ Lien aextr1 aextr2 ajoueur_l
  {-# INLINE unStorable #-}
  type ApiStorableBaseType Lien = CLien
  toStorableBase (Lien aextr1 aextr2 ajoueur_l) f =
    toStorableBase aextr1 $ \aextr1' ->  toStorableBase aextr2 $ \aextr2' ->  toStorableBase ajoueur_l $ \ajoueur_l' ->  f (CLien aextr1' aextr2' ajoueur_l')
  {-# INLINE toStorableBase #-}
  unStorableBase (CLien aextr1' aextr2' ajoueur_l') = do
    aextr1 <- unStorableBase aextr1'
    aextr2 <- unStorableBase aextr2'
    ajoueur_l <- unStorableBase ajoueur_l'
    return $ Lien aextr1 aextr2 ajoueur_l
  {-# INLINE unStorableBase #-}
-- | Représente un champ de contrôle existant.
data Champ = Champ {
      som1 :: Position -- ^ Premier sommet du champ.
  ,   som2 :: Position -- ^ Deuxième sommet du champ.
  ,   som3 :: Position -- ^ Troisième sommet du champ.
  ,   joueur_c :: Int -- ^ Joueur possédant ce champ.
}
  deriving(Show, Eq)
data CChamp = CChamp {
      csom1 :: CPosition -- ^ Premier sommet du champ.
  ,   csom2 :: CPosition -- ^ Deuxième sommet du champ.
  ,   csom3 :: CPosition -- ^ Troisième sommet du champ.
  ,   cjoueur_c :: CInt -- ^ Joueur possédant ce champ.
}
instance Storable CChamp where
  sizeOf    _ = (#size champ)
  {-# INLINE sizeOf #-}
  alignment _ = alignment (undefined :: CInt)
  {-# INLINE alignment #-}
  peek ptr = do
    asom1 <- (#peek champ, som1) ptr
    asom2 <- (#peek champ, som2) ptr
    asom3 <- (#peek champ, som3) ptr
    ajoueur_c <- (#peek champ, joueur_c) ptr
    return $ CChamp asom1 asom2 asom3 ajoueur_c
  {-# INLINE peek #-}
  poke ptr (CChamp asom1 asom2 asom3 ajoueur_c) = do
    (#poke champ, som1) ptr asom1
    (#poke champ, som2) ptr asom2
    (#poke champ, som3) ptr asom3
    (#poke champ, joueur_c) ptr ajoueur_c
  {-# INLINE poke #-}
instance ApiStorable Champ where
  type ApiStorableType Champ = Ptr CChamp
  toStorable (Champ asom1 asom2 asom3 ajoueur_c) f = toStorableBase asom1 $ \asom1' ->  toStorableBase asom2 $ \asom2' ->  toStorableBase asom3 $ \asom3' ->  toStorableBase ajoueur_c $ \ajoueur_c' ->  do
    alloca $ \ptr -> do
      poke ptr $ CChamp asom1' asom2' asom3' ajoueur_c'
      f ptr
  {-# INLINE toStorable #-}
  unStorable ptr = do
    (CChamp asom1' asom2' asom3' ajoueur_c') <- peek ptr
    asom1 <- unStorableBase asom1'
    asom2 <- unStorableBase asom2'
    asom3 <- unStorableBase asom3'
    ajoueur_c <- unStorableBase ajoueur_c'
    return $ Champ asom1 asom2 asom3 ajoueur_c
  {-# INLINE unStorable #-}
  type ApiStorableBaseType Champ = CChamp
  toStorableBase (Champ asom1 asom2 asom3 ajoueur_c) f =
    toStorableBase asom1 $ \asom1' ->  toStorableBase asom2 $ \asom2' ->  toStorableBase asom3 $ \asom3' ->  toStorableBase ajoueur_c $ \ajoueur_c' ->  f (CChamp asom1' asom2' asom3' ajoueur_c')
  {-# INLINE toStorableBase #-}
  unStorableBase (CChamp asom1' asom2' asom3' ajoueur_c') = do
    asom1 <- unStorableBase asom1'
    asom2 <- unStorableBase asom2'
    asom3 <- unStorableBase asom3'
    ajoueur_c <- unStorableBase ajoueur_c'
    return $ Champ asom1 asom2 asom3 ajoueur_c
  {-# INLINE unStorableBase #-}
data CLien_array = CLien_array { cLien_arrayPtr :: Ptr CLien, cLien_arraySize :: CSize }

instance Storable CLien_array where
  sizeOf    _ = (#size lien_array)
  {-# INLINE sizeOf #-}
  alignment _ = alignment (undefined :: CInt)
  {-# INLINE alignment #-}
  peek ptr = do
    length <- (#peek lien_array, length) ptr
    datas <- (#peek lien_array, datas) ptr
    return $ CLien_array datas length
  {-# INLINE peek #-}
  poke ptr (CLien_array datas length) = do
    (#poke lien_array, length) ptr length
    (#poke lien_array, datas) ptr datas
  {-# INLINE poke #-}

instance ApiStorable [Lien] where
  type ApiStorableType [Lien] = Ptr CLien_array
  toStorable xs f = toStorableBase xs $ \a -> alloca $ \ptr -> do
    poke ptr a
    f ptr
  {-# INLINE toStorable #-}
  unStorable xa = do
    (CLien_array xa' xl) <- peek xa
    xs <- peekArray (fromIntegral xl) xa'
    mapM unStorableBase xs
  {-# INLINE unStorable #-}
  type ApiStorableBaseType [Lien] = CLien_array

  toStorableBase xs f = do
    let xl = length xs
    allocaArray xl $ \xa ->
      foldl'
        (\acc (i, c) -> toStorableBase c $ \c' -> do
          poke (advancePtr xa i) c'
          acc
        )
        (f $ CLien_array xa (fromIntegral xl))
        (zip [0..] xs)
  {-# INLINE toStorableBase #-}
  unStorableBase (CLien_array xa xl) = do
    xs <- peekArray (fromIntegral xl) xa
    mapM unStorableBase xs
  {-# INLINE unStorableBase #-}
data CChamp_array = CChamp_array { cChamp_arrayPtr :: Ptr CChamp, cChamp_arraySize :: CSize }

instance Storable CChamp_array where
  sizeOf    _ = (#size champ_array)
  {-# INLINE sizeOf #-}
  alignment _ = alignment (undefined :: CInt)
  {-# INLINE alignment #-}
  peek ptr = do
    length <- (#peek champ_array, length) ptr
    datas <- (#peek champ_array, datas) ptr
    return $ CChamp_array datas length
  {-# INLINE peek #-}
  poke ptr (CChamp_array datas length) = do
    (#poke champ_array, length) ptr length
    (#poke champ_array, datas) ptr datas
  {-# INLINE poke #-}

instance ApiStorable [Champ] where
  type ApiStorableType [Champ] = Ptr CChamp_array
  toStorable xs f = toStorableBase xs $ \a -> alloca $ \ptr -> do
    poke ptr a
    f ptr
  {-# INLINE toStorable #-}
  unStorable xa = do
    (CChamp_array xa' xl) <- peek xa
    xs <- peekArray (fromIntegral xl) xa'
    mapM unStorableBase xs
  {-# INLINE unStorable #-}
  type ApiStorableBaseType [Champ] = CChamp_array

  toStorableBase xs f = do
    let xl = length xs
    allocaArray xl $ \xa ->
      foldl'
        (\acc (i, c) -> toStorableBase c $ \c' -> do
          poke (advancePtr xa i) c'
          acc
        )
        (f $ CChamp_array xa (fromIntegral xl))
        (zip [0..] xs)
  {-# INLINE toStorableBase #-}
  unStorableBase (CChamp_array xa xl) = do
    xs <- peekArray (fromIntegral xl) xa
    mapM unStorableBase xs
  {-# INLINE unStorableBase #-}
data CPosition_array = CPosition_array { cPosition_arrayPtr :: Ptr CPosition, cPosition_arraySize :: CSize }

instance Storable CPosition_array where
  sizeOf    _ = (#size position_array)
  {-# INLINE sizeOf #-}
  alignment _ = alignment (undefined :: CInt)
  {-# INLINE alignment #-}
  peek ptr = do
    length <- (#peek position_array, length) ptr
    datas <- (#peek position_array, datas) ptr
    return $ CPosition_array datas length
  {-# INLINE peek #-}
  poke ptr (CPosition_array datas length) = do
    (#poke position_array, length) ptr length
    (#poke position_array, datas) ptr datas
  {-# INLINE poke #-}

instance ApiStorable [Position] where
  type ApiStorableType [Position] = Ptr CPosition_array
  toStorable xs f = toStorableBase xs $ \a -> alloca $ \ptr -> do
    poke ptr a
    f ptr
  {-# INLINE toStorable #-}
  unStorable xa = do
    (CPosition_array xa' xl) <- peek xa
    xs <- peekArray (fromIntegral xl) xa'
    mapM unStorableBase xs
  {-# INLINE unStorable #-}
  type ApiStorableBaseType [Position] = CPosition_array

  toStorableBase xs f = do
    let xl = length xs
    allocaArray xl $ \xa ->
      foldl'
        (\acc (i, c) -> toStorableBase c $ \c' -> do
          poke (advancePtr xa i) c'
          acc
        )
        (f $ CPosition_array xa (fromIntegral xl))
        (zip [0..] xs)
  {-# INLINE toStorableBase #-}
  unStorableBase (CPosition_array xa xl) = do
    xs <- peekArray (fromIntegral xl) xa
    mapM unStorableBase xs
  {-# INLINE unStorableBase #-}
-- | Déplace votre agent sur la case passée en argument.
deplacer :: Position -> IO Erreur
deplacer dest = toStorable dest $ \dest' ->  (hs_deplacer dest') >>= unStorable

foreign import ccall
  hs_deplacer :: (ApiStorableType Position) ->  IO (ApiStorableType Erreur)
-- | Utilise un turbo.
utiliser_turbo :: IO Erreur
utiliser_turbo  =  (hs_utiliser_turbo ) >>= unStorable

foreign import ccall
  hs_utiliser_turbo ::  IO (ApiStorableType Erreur)
-- | Capture le portail où est positionné votre agent.
capturer :: IO Erreur
capturer  =  (hs_capturer ) >>= unStorable

foreign import ccall
  hs_capturer ::  IO (ApiStorableType Erreur)
-- | Crée un lien entre le portail où se trouve votre agent et le portail de destination donné en argument.
lier :: Position -> IO Erreur
lier portail = toStorable portail $ \portail' ->  (hs_lier portail') >>= unStorable

foreign import ccall
  hs_lier :: (ApiStorableType Position) ->  IO (ApiStorableType Erreur)
-- | Neutralise le portail où se trouve votre agent.
neutraliser :: IO Erreur
neutraliser  =  (hs_neutraliser ) >>= unStorable

foreign import ccall
  hs_neutraliser ::  IO (ApiStorableType Erreur)
-- | Ajoute un bouclier au portail sur lequel se trouve votre agent.
ajouter_bouclier :: IO Erreur
ajouter_bouclier  =  (hs_ajouter_bouclier ) >>= unStorable

foreign import ccall
  hs_ajouter_bouclier ::  IO (ApiStorableType Erreur)
-- | Renvoie la liste de tous les liens présents.
liste_liens :: IO [Lien]
liste_liens  =  (hs_liste_liens ) >>= unStorable

foreign import ccall
  hs_liste_liens ::  IO (ApiStorableType [Lien])
-- | Renvoie la liste de tous les champs de contrôle.
liste_champs :: IO [Champ]
liste_champs  =  (hs_liste_champs ) >>= unStorable

foreign import ccall
  hs_liste_champs ::  IO (ApiStorableType [Champ])
-- | Renvoie la liste de tous les portails de la carte.
liste_portails :: IO [Position]
liste_portails  =  (hs_liste_portails ) >>= unStorable

foreign import ccall
  hs_liste_portails ::  IO (ApiStorableType [Position])
-- | Renvoie la liste de tous les liens existants qui croisent un segment, entravant la création d'un lien.
liens_bloquants :: Position ->  Position -> IO [Lien]
liens_bloquants ext1 ext2 = toStorable ext1 $ \ext1' ->  toStorable ext2 $ \ext2' ->  (hs_liens_bloquants ext1' ext2') >>= unStorable

foreign import ccall
  hs_liens_bloquants :: (ApiStorableType Position) -> (ApiStorableType Position) ->  IO (ApiStorableType [Lien])
-- | Prend les positions de deux portails, et renvoie un booléen indiquant s'ils sont reliés. Le résultat est `false` lorsque l'une des deux positions ne repère pas un portail.
lien_existe :: Position ->  Position -> IO Bool
lien_existe ext1 ext2 = toStorable ext1 $ \ext1' ->  toStorable ext2 $ \ext2' ->  (hs_lien_existe ext1' ext2') >>= unStorable

foreign import ccall
  hs_lien_existe :: (ApiStorableType Position) -> (ApiStorableType Position) ->  IO (ApiStorableType Bool)
-- | Renvoie un booléen indiquant si les 3 positions repèrent bien 3 portails tous reliés entre eux.
champ_existe :: Position ->  Position ->  Position -> IO Bool
champ_existe som1 som2 som3 = toStorable som1 $ \som1' ->  toStorable som2 $ \som2' ->  toStorable som3 $ \som3' ->  (hs_champ_existe som1' som2' som3') >>= unStorable

foreign import ccall
  hs_champ_existe :: (ApiStorableType Position) -> (ApiStorableType Position) -> (ApiStorableType Position) ->  IO (ApiStorableType Bool)
-- | Renvoie un booléen indiquant si la case ``pos`` se trouve dans un champ.
case_dans_champ :: Position -> IO Bool
case_dans_champ pos = toStorable pos $ \pos' ->  (hs_case_dans_champ pos') >>= unStorable

foreign import ccall
  hs_case_dans_champ :: (ApiStorableType Position) ->  IO (ApiStorableType Bool)
-- | Renvoie la liste des champs à l'intérieur desquels ``pos`` se trouve. Si la case est un portail, le résultat de ``case_champs`` sera disjoint de celui de ``champs_incidents_portail``.
case_champs :: Position -> IO [Champ]
case_champs pos = toStorable pos $ \pos' ->  (hs_case_champs pos') >>= unStorable

foreign import ccall
  hs_case_champs :: (ApiStorableType Position) ->  IO (ApiStorableType [Champ])
-- | Renvoie le numéro du joueur correspondant au portail donné, -1 si le portail est neutre, -2 si la case n'est pas un portail. Vous pouvez utiliser cette fonction pour vérifier qu'une case donnée est bien un portail.
portail_joueur :: Position -> IO Int
portail_joueur portail = toStorable portail $ \portail' ->  (hs_portail_joueur portail') >>= unStorable

foreign import ccall
  hs_portail_joueur :: (ApiStorableType Position) ->  IO (ApiStorableType Int)
-- | Renvoie le nombre de boucliers présents sur un portail (-2 si la case n'est pas un portail).
portail_boucliers :: Position -> IO Int
portail_boucliers portail = toStorable portail $ \portail' ->  (hs_portail_boucliers portail') >>= unStorable

foreign import ccall
  hs_portail_boucliers :: (ApiStorableType Position) ->  IO (ApiStorableType Int)
-- | Renvoie la liste de tous les liens dont le portail donné est une extrémité.
liens_incidents_portail :: Position -> IO [Lien]
liens_incidents_portail portail = toStorable portail $ \portail' ->  (hs_liens_incidents_portail portail') >>= unStorable

foreign import ccall
  hs_liens_incidents_portail :: (ApiStorableType Position) ->  IO (ApiStorableType [Lien])
-- | Renvoie la liste de tous les champs dont le portail donné est un sommet.
champs_incidents_portail :: Position -> IO [Champ]
champs_incidents_portail portail = toStorable portail $ \portail' ->  (hs_champs_incidents_portail portail') >>= unStorable

foreign import ccall
  hs_champs_incidents_portail :: (ApiStorableType Position) ->  IO (ApiStorableType [Champ])
-- | Renvoie la liste de tous les champs dont le lien donné est un côté. Si le segment n'est pas un lien présent, renvoie la liste de tous les champs que la création du lien ferait apparaître.
champs_incidents_segment :: Position ->  Position -> IO [Champ]
champs_incidents_segment ext1 ext2 = toStorable ext1 $ \ext1' ->  toStorable ext2 $ \ext2' ->  (hs_champs_incidents_segment ext1' ext2') >>= unStorable

foreign import ccall
  hs_champs_incidents_segment :: (ApiStorableType Position) -> (ApiStorableType Position) ->  IO (ApiStorableType [Champ])
-- | Renvoie la liste des portails capturés par votre adversaire au dernier tour.
hist_portails_captures :: IO [Position]
hist_portails_captures  =  (hs_hist_portails_captures ) >>= unStorable

foreign import ccall
  hs_hist_portails_captures ::  IO (ApiStorableType [Position])
-- | Renvoie la liste des portails neutralisés par votre adversaire au dernier tour. Cela inclut toutes les utilisations de virus.
hist_portails_neutralises :: IO [Position]
hist_portails_neutralises  =  (hs_hist_portails_neutralises ) >>= unStorable

foreign import ccall
  hs_hist_portails_neutralises ::  IO (ApiStorableType [Position])
-- | Renvoie la liste des liens créés par votre adversaire au dernier tour.
hist_liens_crees :: IO [Lien]
hist_liens_crees  =  (hs_hist_liens_crees ) >>= unStorable

foreign import ccall
  hs_hist_liens_crees ::  IO (ApiStorableType [Lien])
-- | Renvoie la liste des champs créés par votre adversaire au dernier tour.
hist_champs_crees :: IO [Champ]
hist_champs_crees  =  (hs_hist_champs_crees ) >>= unStorable

foreign import ccall
  hs_hist_champs_crees ::  IO (ApiStorableType [Champ])
-- | Renvoie la liste des positions où votre adversaire a ajouté des boucliers au dernier tour.
hist_boucliers_ajoutes :: IO [Position]
hist_boucliers_ajoutes  =  (hs_hist_boucliers_ajoutes ) >>= unStorable

foreign import ccall
  hs_hist_boucliers_ajoutes ::  IO (ApiStorableType [Position])
-- | Renvoie la distance de Manhattan entre deux positions.
distance :: Position ->  Position -> IO Int
distance pos1 pos2 = toStorable pos1 $ \pos1' ->  toStorable pos2 $ \pos2' ->  (hs_distance pos1' pos2') >>= unStorable

foreign import ccall
  hs_distance :: (ApiStorableType Position) -> (ApiStorableType Position) ->  IO (ApiStorableType Int)
-- | Renvoie le nombre de points que rapporte(rait) chaque tour un champ existant ou hypothétique.
score_triangle :: Position ->  Position ->  Position -> IO Int
score_triangle som1 som2 som3 = toStorable som1 $ \som1' ->  toStorable som2 $ \som2' ->  toStorable som3 $ \som3' ->  (hs_score_triangle som1' som2' som3') >>= unStorable

foreign import ccall
  hs_score_triangle :: (ApiStorableType Position) -> (ApiStorableType Position) -> (ApiStorableType Position) ->  IO (ApiStorableType Int)
-- | Indique si deux segments se croisent. Cette fonction correspond exactement à la condition d'interférence entre liens, c'est-à-dire qu'elle renvoie ``false`` si l'intersection est une extrémité des deux segments.
intersection_segments :: Position ->  Position ->  Position ->  Position -> IO Bool
intersection_segments a1 a2 b1 b2 = toStorable a1 $ \a1' ->  toStorable a2 $ \a2' ->  toStorable b1 $ \b1' ->  toStorable b2 $ \b2' ->  (hs_intersection_segments a1' a2' b1' b2') >>= unStorable

foreign import ccall
  hs_intersection_segments :: (ApiStorableType Position) -> (ApiStorableType Position) -> (ApiStorableType Position) -> (ApiStorableType Position) ->  IO (ApiStorableType Bool)
-- | Indique si un point se trouve à l'intérieur d'un triangle. Le critère coïncide avec celui de ``case_champs``.
point_dans_triangle :: Position ->  Position ->  Position ->  Position -> IO Bool
point_dans_triangle p som1 som2 som3 = toStorable p $ \p' ->  toStorable som1 $ \som1' ->  toStorable som2 $ \som2' ->  toStorable som3 $ \som3' ->  (hs_point_dans_triangle p' som1' som2' som3') >>= unStorable

foreign import ccall
  hs_point_dans_triangle :: (ApiStorableType Position) -> (ApiStorableType Position) -> (ApiStorableType Position) -> (ApiStorableType Position) ->  IO (ApiStorableType Bool)
-- | Renvoie votre numéro de joueur.
moi :: IO Int
moi  =  (hs_moi ) >>= unStorable

foreign import ccall
  hs_moi ::  IO (ApiStorableType Int)
-- | Renvoie le numéro de votre adversaire.
adversaire :: IO Int
adversaire  =  (hs_adversaire ) >>= unStorable

foreign import ccall
  hs_adversaire ::  IO (ApiStorableType Int)
-- | Indique la position de l'agent du joueur désigné par le numéro ``id_joueur``.
position_agent :: Int -> IO Position
position_agent id_joueur = toStorable id_joueur $ \id_joueur' ->  (hs_position_agent id_joueur') >>= unStorable

foreign import ccall
  hs_position_agent :: (ApiStorableType Int) ->  IO (ApiStorableType Position)
-- | Indique votre nombre de points d'actions restants pour ce tour-ci.
points_action :: IO Int
points_action  =  (hs_points_action ) >>= unStorable

foreign import ccall
  hs_points_action ::  IO (ApiStorableType Int)
-- | Indique votre nombre de points de déplacement restants pour ce tour-ci.
points_deplacement :: IO Int
points_deplacement  =  (hs_points_deplacement ) >>= unStorable

foreign import ccall
  hs_points_deplacement ::  IO (ApiStorableType Int)
-- | Renvoie le score du joueur désigné par le numéro ``id_joueur``.
score :: Int -> IO Int
score id_joueur = toStorable id_joueur $ \id_joueur' ->  (hs_score id_joueur') >>= unStorable

foreign import ccall
  hs_score :: (ApiStorableType Int) ->  IO (ApiStorableType Int)
-- | Renvoie le numéro du tour actuel.
tour_actuel :: IO Int
tour_actuel  =  (hs_tour_actuel ) >>= unStorable

foreign import ccall
  hs_tour_actuel ::  IO (ApiStorableType Int)
-- | Annule la dernière action. Renvoie ``false`` quand il n'y a pas d'action à annuler ce tour-ci.
annuler :: IO Bool
annuler  =  (hs_annuler ) >>= unStorable

foreign import ccall
  hs_annuler ::  IO (ApiStorableType Bool)
-- | Affiche le contenu d'une valeur de type erreur
afficher_erreur :: Erreur -> IO ()
afficher_erreur v = toStorable v $ \v' ->  (hs_afficher_erreur v') >>= unStorable

foreign import ccall
  hs_afficher_erreur :: (ApiStorableType Erreur) ->  IO (ApiStorableType ())
-- | Affiche le contenu d'une valeur de type position
afficher_position :: Position -> IO ()
afficher_position v = toStorable v $ \v' ->  (hs_afficher_position v') >>= unStorable

foreign import ccall
  hs_afficher_position :: (ApiStorableType Position) ->  IO (ApiStorableType ())
-- | Affiche le contenu d'une valeur de type lien
afficher_lien :: Lien -> IO ()
afficher_lien v = toStorable v $ \v' ->  (hs_afficher_lien v') >>= unStorable

foreign import ccall
  hs_afficher_lien :: (ApiStorableType Lien) ->  IO (ApiStorableType ())
-- | Affiche le contenu d'une valeur de type champ
afficher_champ :: Champ -> IO ()
afficher_champ v = toStorable v $ \v' ->  (hs_afficher_champ v') >>= unStorable

foreign import ccall
  hs_afficher_champ :: (ApiStorableType Champ) ->  IO (ApiStorableType ())
