(*
** This file has been generated, if you wish to
** modify it in a permanent way, please refer
** to the script file : gen/generator_caml.rb
*)

module A = Array
module L = List
module P = Api

(* marche aléatoire lol *)

let nb_turbos = P.nb_points_action / P.cout_turbo
let deplacement = P.nb_points_deplacement + nb_turbos * P.gain_turbo

let nonempty_list_to_array ((x::_) as l) =
  let t = A.make (L.length l) x in
  let rec loop i = function
    | [] -> ()
    | y::ys -> t.(i) <- y; loop (i+1) ys in
  loop 0 l;
  t

let in_place_shuffle t =
  let n = A.length t in
  let swap j k = let tmp = t.(j) in
                 t.(j) <- t.(k); t.(k) <- tmp in
  for i = 0 to n-1 do
    swap i (i + Random.int (n-i))
  done;
  t

let shuffle_list l =
  if l = [] then [] else
    A.to_list (in_place_shuffle (nonempty_list_to_array l))
       
let for_pos_in_terrain f = 
  for x = 0 to P.taille_terrain - 1 do
    for y = 0 to P.taille_terrain - 1 do
      f x y
    done
  done

let norm_1_ball (x,y) =
  let r = deplacement and l = ref [] in
  for i = max (x-r) 0 to min (x+r) (P.taille_terrain-1) do
    for j = max (y-r) 0 to min (y+r) (P.taille_terrain-1) do
      if P.distance (x,y) (i,j) <= r
      then l := (i,j) :: !l
    done
  done;
  shuffle_list !l

(*
** Fonction appelée au début de la partie
*)
let partie_init () =  (* Pose ton code ici *)
  flush stderr; flush stdout;; (* Pour que vos sorties s'affichent *)

(*
** Fonction appelée à chaque tour
*)
let jouer_tour () =  (* Pose ton code ici *)
  for i = 1 to nb_turbos do
    P.utiliser_turbo ();
  done;
  P.deplacer (L.hd (norm_1_ball (P.position_agent (P.moi ()))));
  flush stderr; flush stdout;; (* Pour que vos sorties s'affichent *)

(*
** Fonction appelée à la fin de la partie
*)
let partie_fin () =  (* Pose ton code ici *)
  flush stderr; flush stdout;; (* Pour que vos sorties s'affichent *)

(* /!\ Ne touche pas a ce qui suit /!\ *)
Callback.register "ml_partie_init" partie_init;;Callback.register "ml_jouer_tour" jouer_tour;;Callback.register "ml_partie_fin" partie_fin;;
