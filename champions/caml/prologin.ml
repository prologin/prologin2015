(*
** This file has been generated, if you wish to
** modify it in a permanent way, please refer
** to the script file : gen/generator_caml.rb
*)

open Api;;

let fin_action_bouclier = 9

let coefLiens nb_liens tour = (4. +. max 3. nb_liens) *. 100.
let coefChamp tour = 1.
let coefBoucliers tour = 0.
let coefPortails tour = 1.

let coef_me = 1.
let coef_adv = -1.

let coef_fuit distance tour = float_of_int distance

let score_position ma_distance sa_distance =
  (10. +. float_of_int sa_distance) *. 100. /. (1. +. float_of_int ma_distance)

module Position = struct
  type t = position
  let compare a b = compare a b
end

module PosSet = Set.Make(Position)
module PosMap = Map.Make(Position)

module LiensSet = struct
  let empty = PosMap.empty
  let add (a, b) map =
    let pt0 = min a b in
    let pt1 = max a b in
    let set = try PosMap.find pt0 map with Not_found -> PosSet.empty
    in PosMap.add pt0 (PosSet.add pt1 set) map

  let to_list map =
    PosMap.fold (fun pt1 v acc ->
      PosSet.fold (fun pt2 acc -> (pt1, pt2) :: acc) v acc) map []
end

(*nombre de tours nécéssaires pour capturer un lien qui est à cette distance*)
let ntours_a_porte d = d / (nb_points_deplacement + nb_points_action / cout_turbo)


let (|>) x f = f x


let refmoi = ref (-1)
let moi () = !refmoi

let position_valide (x, y) = x >= 0 && y >= 0 && x < taille_terrain && y < taille_terrain



let ppos p (x, y) = Printf.fprintf p "(%d, %d)" x y
let scale a (x, y) = a * x, a * y
let pos_add (x1, y1) (x2, y2) = (x1 + x2, y1 + y2)

type cout = { pa : int; pd : int}
let (++) c1 c2 = { pa = c1.pa + c2.pa; pd = c1.pd + c2.pd }
let cout_free = { pa = 0; pd = 0}
let cout_normalise c = c.pa + c.pd * cout_turbo
let cout_scale a c = { pa = c.pa * a; pd = c.pd * a}
let cout_lien = { pa=cout_lien; pd=0 }
let cout_neutralisation_capture b =
  let a = cout_neutralisation + cout_neutralisation_bouclier * b + cout_capture in
  if a > cout_virus then {pa=cout_virus; pd=0}
  else {pa=a; pd=0}
let cout_bouclier = { pa=cout_bouclier; pd=0}
let cout_capture = { pa=cout_capture; pd=0 }
let cout_neutralisation = { pa=cout_neutralisation; pd=0 }

let (--) moyens cout =
  let retenue = max 0 (cout.pd - moyens.pd) in
  { pa= moyens.pa - cout.pa - retenue * cout_turbo; pd=moyens.pd - cout.pd + retenue}

let mes_moyens moyens cout = (moyens -- cout).pa >= 0

let pcout p c = Printf.fprintf p "{a:%d, d:%d}" c.pa c.pd

type owner = Me | Adv | Neutral
let powner p = function
  | Me -> Printf.fprintf p "Me"
  | Adv -> Printf.fprintf p "Adv"
  | Neutral -> Printf.fprintf p "Neutral"

let owner i = if i = -1 then Neutral else if i = moi () then Me else Adv

type portail = {
    pos : position;
    owned : owner;
    champs : champ list;
    liens : PosSet.t;
    boucliers : int;
    deja : bool;
  }

let perr p () = Printf.fprintf p "\027[31mErreur! \027[0m"

let pdebug state =
  Printf.printf "mon état interne : \n";
  PosMap.iter (fun _ p -> if p.owned = Me then
    begin
      Printf.printf "sommet %a\n" ppos p.pos;
      List.iter (fun c -> Printf.printf "  champ : %a %a %a\n" ppos c.som1 ppos c.som2 ppos c.som3) p.champs;
      PosSet.iter (fun c -> Printf.printf "  lien : -> %a\n" ppos c) p.liens;
    end) state

let afficher_erreur state = function Ok -> ()
| Pa_insuffisants    -> Printf.printf "%aVous ne possédez pas assez de points d'action pour cette action.\n" perr ()
| Aucun_portail      -> Printf.printf "%aLa position spécifiée n'est pas un portail.\n" perr ()
| Position_invalide  -> Printf.printf "%aLa position spécifiée est hors de la carte.\n" perr ()
| Position_eloignee  -> Printf.printf "%aLa destination est trop éloignée.\n" perr ()
| Portail_ami        -> Printf.printf "%aLe portail vous appartient.\n" perr ()
| Portail_neutre     -> Printf.printf "%aLe portail est neutre.\n" perr ()
| Portail_ennemi     -> Printf.printf "%aLe portail appartient à votre adversaire.\n" perr ()
| Lien_intersection  -> Printf.printf "%aLe lien croise un lien existant.\n" perr ()
| Lien_champ         ->
    Array.iter (fun p ->
      if portail_joueur p = moi () then
        let t = champs_incidents_portail p in
        if (Array.length t) != 0 then begin
          Printf.printf "sommet %a\n" ppos p;
          Array.iter
            (fun c -> Printf.printf "  champ %a %a %a\n" ppos c.som1 ppos c.som2 ppos c.som3)
            t
        end)
      (liste_portails ());
    pdebug state;
    Printf.printf "%aLe lien se trouve dans un champ existant.\n" perr ()
| Lien_degenere      -> Printf.printf "%aLes deux extrémités du lien coïncident.\n" perr ()
| Limite_boucliers   -> Printf.printf "%aCe portail est équipé du nombre maximal de boucliers.\n" perr ()

let rec aller_vers pos state =
  let mypos = position_agent (moi ()) in
  if mypos = pos then () else
  if points_deplacement () = 0 then () else
  let acote = List.map (pos_add mypos) [0, 1; 1, 0; 0, -1; -1, 0] in
  let acote = List.map (fun p -> distance pos p, p) acote in
  let acote = List.sort (fun (a, _) (b, _) -> a - b) acote |> List.map snd in
  deplacer (List.hd acote) |> afficher_erreur state;
  aller_vers pos state


let peut_relier pos1 pos2 portails =
  pos1 <> pos2 &&
  PosMap.for_all (fun _ p ->
    PosSet.for_all (fun l -> not(intersection_segments pos1 pos2 p.pos l)) p.liens
 &&   List.for_all (fun c -> not(point_dans_triangle pos1 c.som1 c.som2 c.som3) &&
      not(point_dans_triangle pos2 c.som1 c.som2 c.som3)) p.champs
               ) portails

(* TODO intégrer la constante gain_turbo *)
let cout_deplacement pos1 pos2 nb_points_deplacement =
  let d = distance pos1 pos2 in
  let pd = min d nb_points_deplacement in
  { pa = cout_turbo * (d - pd);
    pd = pd }

let move state resources pos1 pos2 () =
  let cout = cout_deplacement pos1 pos2 resources.pd in
  for i = 1 to cout.pa / cout_turbo do
    utiliser_turbo () |> afficher_erreur state
  done;
  Printf.printf "Move to : %a (distance : %d) (cout : %a)\n%!"
    ppos pos2 (distance pos1 pos2) pcout cout;
  deplacer pos2 |> afficher_erreur state

let capture state p () = 
  Printf.printf "Capture %a !\n" ppos p.pos;
  capturer () |> afficher_erreur state

let creation_lien state pos () =
  Printf.printf "Creation lien to %a\n" ppos pos;
  lier pos |> afficher_erreur state

let nop () = ()

let ajouter_bouclier state p () =
  Printf.printf "Ajouter bouclier %a\n" ppos p.pos;
  ajouter_bouclier () |> afficher_erreur state

let neutralisation_capture state p () =
  if (cout_neutralisation_capture p.boucliers).pa = cout_virus then
    begin
      Printf.printf "Virus capture %a\n" ppos p.pos;
      utiliser_virus () |> afficher_erreur state;
    end
  else
    begin
      Printf.printf "Neutralisation capture %a\n" ppos p.pos;
      neutraliser () |> afficher_erreur state;
      capturer () |> afficher_erreur state;
    end

let neutralisation_capture_bouclier state p () =
  neutralisation_capture state p ();
  ajouter_bouclier state p ()

let filtermap f li =
  List.fold_right (fun x acc -> match f x with
  | None -> acc
  | Some x -> x::acc) li []

let state_relier p1 p2 portails =
  let moi = moi () in
  let linked p = (PosMap.find p portails).liens in
  let linked_p1 = linked p1 in
  let linked_p2 = linked p2 in
  let linked_both = PosSet.inter linked_p2 linked_p1 in
  let nouveaux_champs = PosSet.fold (fun p acc ->
    {som1=p1; som2=p2; som3=p; joueur_c= moi} :: acc) linked_both [] in

  let f p p2 portails = PosMap.add p.pos
      {p with liens = PosSet.add p2 p.liens; champs = List.rev_append nouveaux_champs p.champs} portails in
  let portails = f (PosMap.find p1 portails) p2 portails in
  let portails = f (PosMap.find p2 portails) p1 portails in
  PosSet.fold (fun l portails ->
    let p = PosMap.find l portails in
    PosMap.add l {p with champs = List.rev_append nouveaux_champs p.champs} portails
              ) linked_both portails

let state_neutralisation_capture b p p2 =
  if p.pos = p2.pos then
    { p2 with
      owned = Me;
      liens = PosSet.empty;
      champs =  [];
      boucliers = b;
    }
  else { p2 with
         liens = PosSet.remove p.pos p2.liens;
         champs = List.filter (fun c -> c.som1 <> p.pos && c.som2 <> p.pos && c.som3 <> p.pos) p2.champs }

(*
** Fonction appelée au début de la partie
*)
let partie_init () =
  refmoi := Api.moi ();
  flush stderr; flush stdout;; (* Pour que vos sorties s'affichent *)

let actions_relier p position resources portails actions =
  let points_reliables = PosMap.fold (fun _ p2 set ->
    if p2.owned = Me && peut_relier p.pos p2.pos portails then
      PosSet.add p2.pos set
    else set) portails PosSet.empty in
  let liens =
    PosSet.fold (fun point acc ->
      let liens = (PosMap.find point portails).liens in
      PosSet.fold (fun l acc -> if l < point then (l, point) :: acc
      else acc) (PosSet.inter points_reliables liens) acc) points_reliables [] in
  let liens = List.map (fun (p1, p2) -> score_triangle position p1 p2, p1, p2) liens in
  let liens = List.sort (fun (a, _, _) (b, _, _) -> a - b) liens in
  let len = List.length liens in
  (* TODO virer les triangles qui sont alignés avec d'autres triangles. créer les petits nous empeche de créer les grands *)
  if len > 0 && mes_moyens resources (cout_scale 2 cout_lien) then (* si on ne peut meme pas en prendre 1, alors on va créer une nop et c'est clairement pas le but ici. *)
    let _deja, resources, act, state = List.fold_left (fun (deja, resources, act0, state) (_, p1, p2) ->
      let fp p' need_resources state deja =
        if PosSet.mem p' deja then deja, need_resources, nop, state
        else PosSet.add p' deja, need_resources ++ cout_lien, creation_lien state p',
          state_relier p.pos p' state
      in
      let        need_resources = cout_free in
      let deja2, need_resources, act1, state2 = fp p1 need_resources state deja in
      let deja2, need_resources, act2, state2 = fp p2 need_resources state2 deja2 in

      if mes_moyens resources need_resources then
        (deja2, resources -- need_resources, (fun () ->
          act0 (); act1 (); act2 ()), state2)
      else (deja, resources, act0, state))
      (PosSet.empty, resources, nop, portails) liens
    in (position, resources, act, state)::actions
  else
  if mes_moyens resources cout_lien && points_reliables <> PosSet.empty then
(* on tente de la relier à tout les points *)
    let points_reliables = PosSet.fold (fun p' acc -> p'::acc) points_reliables [] in
    let points_reliables = List.map (fun p' -> distance p.pos p', p') points_reliables in
    let points_reliables = List.sort (fun (a, _) (b, _) -> b - a) points_reliables in
    let points_reliables = List.map snd points_reliables in
    let resources, action, state = List.fold_left
        (fun (resources, action, state) p' ->
          if mes_moyens resources cout_lien then
            resources -- cout_lien, (fun () ->
              action ();
              creation_lien state p' ()), state_relier p.pos p' state
          else resources, action, state
        ) (resources, nop, portails) points_reliables
    in (position, resources, action, state) :: actions
  else actions

let possibles neutralises position resources portails = (* TODO flatten un peu tout ça... *)
  let owner =
    try Some (PosMap.find position portails).owned
    with Not_found -> None
  in
  let in_opponent = owner = Some Adv in
  let in_neutral = owner = Some Neutral in
  PosMap.fold (fun _ p actions ->
    if position = p.pos then
      match p.owned with
      | Me -> (* on relie *)
          let actions = if mes_moyens resources cout_lien then
            actions_relier p position resources portails actions else actions
          in if p.boucliers < 3 && resources.pa < fin_action_bouclier
              && mes_moyens resources cout_bouclier then
            (position, resources -- cout_bouclier, ajouter_bouclier portails p,
             PosMap.add p.pos {p with boucliers = p.boucliers + 1} portails
(* on ajoute une action ou on place juste un bouclier *)
            ) :: actions
          else actions
      | Adv ->
          if PosSet.mem position neutralises then
            actions
          else
          let cout = cout_neutralisation_capture p.boucliers ++ cout_bouclier in
          if mes_moyens resources cout then
            (position, resources -- cout, neutralisation_capture_bouclier portails p,
             PosMap.map (state_neutralisation_capture 1 p) portails) :: actions
          else
            let cout = cout_neutralisation_capture p.boucliers in
            if mes_moyens resources cout then
              (position, resources -- cout, neutralisation_capture portails p,
               PosMap.map (state_neutralisation_capture 0 p) portails) :: actions
            else actions
      | Neutral -> (* on capture *)
          if mes_moyens resources cout_capture then
            (position, resources -- cout_capture, capture portails p,
             PosMap.add p.pos {p with owned = Me } portails) :: actions
          else actions
    else if not in_neutral then (* on se déplace vers un des portails *)
      let cout = cout_deplacement p.pos position resources.pd in
      if mes_moyens resources cout && not p.deja then
        (p.pos, resources -- cout, move portails resources position p.pos,
        PosMap.add p.pos {p with deja = true} portails) :: actions
      else actions
    else actions)
    portails []

let possibles neutralises =
  let f ((position, resources, action, portails) as tuple) =
    let li = possibles neutralises position resources portails in
    match li with
    | [] -> [tuple], []
    | _ -> [], List.map (fun (pos, resources, action2, portails) ->
          (pos, resources, (fun () -> action2 (action ())), portails)) li
  in
  let rec eat lief node =
    let lief2, node = List.map f node |> List.split in
    let lief = List.flatten (lief::lief2) in
    let node = List.flatten node in
    let lennode = List.length node in
    if lennode = 0 || lennode > 100 then
      List.append node lief
    else eat lief node
  in (fun position resources portails ->
    eat [] [position, resources, nop, portails] |> List.filter (fun (_, r, _, _) -> r <> resources ))

(* TODO jouer sur ces constantes *)
let delta_score tour portails =
  let opponent_position = position_agent (adversaire ()) in
  PosMap.fold (fun pos p delta -> if p.owned = Neutral then delta else
  let deltachamps = List.fold_left (fun deta c ->
    deta + score_triangle c.som1 c.som2 c.som3) 0 p.champs in
  let deltalien = PosSet.cardinal p.liens |> float_of_int in
  let deltaportail = 1. in
  let delta_boucliers = float_of_int p.boucliers *. deltalien in
  let sign = match p.owned with Me -> coef_me | Adv -> coef_adv | Neutral -> 0. in
  delta +. sign *. ( delta_boucliers *. coefBoucliers tour
                     +. coefLiens deltalien tour
                     +. deltaportail *. coefPortails tour
                     +. float_of_int  deltachamps *. coefChamp tour)) portails 0.

let score_position opponent_position tour mypos portails =
  let nos_distances = distance mypos opponent_position in
  let n, sum = PosMap.fold (fun pos p (n, sum) ->
    if p.owned = Adv then
      let d = distance mypos pos |> ntours_a_porte in
      let d2 = distance opponent_position pos |> ntours_a_porte in
      let diff = score_position d d2 in
      let coef = float_of_int (PosSet.cardinal p.liens) in
      n +. coef, sum +. diff *. coef
    else n, sum) portails (0., 0.)
  in
  if n < 1. then 1000000. else sum /. n +. coef_fuit nos_distances tour


let pick_action score_avant resources actions =
  let opponent_position = position_agent (adversaire ()) in
  let tour = tour_actuel () in
  match actions with
  | [] ->
      Printf.printf "pas d'action ?\n%!";
      assert false
  | ((pos0, res0, _, portails) as hd)::tl ->
      let score0 = delta_score tour portails +. score_position opponent_position tour pos0 portails in
      List.fold_left (fun (score1, res1, act1) ((pos2, res2, _, portails) as act2)->
        let res2 = cout_normalise (resources -- res2) in
        let score2 = delta_score tour portails +. score_position opponent_position tour pos2 portails in
        (* if (score2 - score_avant) * res1 > (score1 - score_avant) * res2 *)
        if score2 > score1
        then score2, res2, act2 else score1, res1, act1
                     ) (score0, cout_normalise (resources -- res0), hd) tl

(*
** Fonction appelée à chaque tour
*)
let jouer_tour () =
Printf.printf "Tour : %d, mon score : %d, autre score : %d\n%!"
    (tour_actuel ())
    (score (moi ()))
    (score (adversaire ()));
  let neutralises = hist_portails_neutralises () |> Array.to_list |> PosSet.of_list in
  Printf.printf "%d Neutralisés ?\n%!" (PosSet.cardinal neutralises);
  let moi = moi () in
  let mypos = position_agent moi in
  let mes_resources = {pa=nb_points_action ; pd=nb_points_deplacement} in
  let portails = liste_portails () |> Array.to_list |>
  List.map (fun pos -> {
    pos=pos;
    owned = owner (portail_joueur pos);
    champs = champs_incidents_portail pos |> Array.to_list;
    liens = liens_incidents_portail pos |> Array.to_list |> List.map (fun l -> if l.extr1 = pos then l.extr2 else l.extr1) |> PosSet.of_list;
    boucliers = portail_boucliers pos;
    deja = mypos = pos
  }) |> List.fold_left (fun acc p -> PosMap.add p.pos p acc) PosMap.empty
  in
  let rec f position resources portails =
    let p = possibles neutralises position resources portails in
    if p <> [] then
      let score_avant = delta_score (tour_actuel ()) portails in
      begin
        (* intelligence ici *)
        let delta, _, (position, resources, action, portails) = pick_action score_avant resources p in
        Printf.printf "delta : %f. %d actions possibles resources restantes : %a\n%!" delta (List.length p) pcout resources;
        action () ;
        f position resources portails
      end
    else (position, resources, portails) in
  let position, resources, portails = f mypos mes_resources portails in
  Printf.printf "resources a la fin : %d %d\n"
    (points_action ())
    (points_deplacement ());
  while points_action () >= cout_turbo do
    utiliser_turbo () |> afficher_erreur portails;
  done;
  Printf.printf "resources apres_turbo : %d %d\n"
    (points_action ())
    (points_deplacement ());
(* TODO calculer si il nous restera des points d'actions à la fin pour ajouter des boucliers *)
(* TODO se calculer des scores pour tout les points qu'on peut atteindre *)
  let score_bestpos, target_position =
  PosMap.fold (fun pos2 p (score, pos)->
    let score2 = match p.owned with
    | Me -> 1000.
    | Adv ->
        let deltachamps = List.fold_left (fun deta c ->
          deta + score_triangle c.som1 c.som2 c.som3) 0 p.champs in

        float_of_int (distance pos2 position) *.
          (100. -. float_of_int (PosSet.cardinal p.liens))
          /. float_of_int deltachamps
    | Neutral -> float_of_int (distance pos2 position) *. 1000.
    in if score2 < score then score2, pos2 else score, pos)
      portails (2000., (0, 0)) in
  Printf.printf "le point le plus intéressant est en : %a (score : %f)\n%!" ppos target_position score_bestpos;
  aller_vers target_position portails ;
  flush stderr; flush stdout

(*
** Fonction appelée à la fin de la partie
*)
let partie_fin () =
  flush stderr; flush stdout;; (* Pour que vos sorties s'affichent *)

(* /!\ Ne touche pas a ce qui suit /!\ *)
Callback.register "ml_partie_init" partie_init;;Callback.register "ml_jouer_tour" jouer_tour;;Callback.register "ml_partie_fin" partie_fin;;
