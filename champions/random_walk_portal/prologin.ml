(*
** This file has been generated, if you wish to
** modify it in a permanent way, please refer
** to the script file : gen/generator_caml.rb
*)

open Batteries
module P = Api

(* marche aléatoire lol *)

let nb_turbos = P.nb_points_action / P.cout_turbo - 1
let deplacement = P.nb_points_deplacement + nb_turbos

(*
** Fonction appelée au début de la partie
*)
let partie_init () =  (* Pose ton code ici *)
  Random.self_init ();
  flush stderr; flush stdout;; (* Pour que vos sorties s'affichent *)

(*
** Fonction appelée à chaque tour
*)
let jouer_tour () =  (* Pose ton code ici *)
  let portails = Array.enum @@ P.liste_portails () in
  for i = 1 to nb_turbos do
    P.utiliser_turbo ();
  done;
  begin try
      while true do
        let mypos = P.position_agent @@ P.moi () in
        let movepts = P.points_deplacement () in
        let rand_portail = portails
                           |> Enum.filter
                                (fun p -> P.distance p mypos <= movepts)
                           |> Random.choice in
        P.deplacer rand_portail;
        P.capturer ();
        portails |> Random.choice |> P.lier
      done
    with
    | Enum.No_more_elements -> ()
  end;
  flush stderr; flush stdout;; (* Pour que vos sorties s'affichent *)

(*
** Fonction appelée à la fin de la partie
*)
let partie_fin () =  (* Pose ton code ici *)
  flush stderr; flush stdout;; (* Pour que vos sorties s'affichent *)

(* /!\ Ne touche pas a ce qui suit /!\ *)
Callback.register "ml_partie_init" partie_init;;
Callback.register "ml_jouer_tour" jouer_tour;;
Callback.register "ml_partie_fin" partie_fin;;
