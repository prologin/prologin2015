(* génère une solution au problème des 13 dames :D *)

Random.self_init ()

let in_place_shuffle t =
  let n = Array.length t in
  let swap j k = let tmp = t.(j) in
                 t.(j) <- t.(k); t.(k) <- tmp in
  for i = 0 to n-1 do
    swap i (i + Random.int (n-i))
  done;
  t

let gen_n_queens n =
  let rec f k vert diag_l diag_r acc =
    if k = n then Some acc else (
      let free = Array.make (n-k) (-1) in
      let mask = vert lor diag_l lor diag_r in
      let j = ref 0 in
      for i = 0 to n-1 do
        if (1 lsl i) land mask = 0 then (
          free.(!j) <- i;
          incr j
        )
      done;
      in_place_shuffle free;
      let rec first_ok ip =
        if ip >= n-k then None
        else let p = free.(ip) in
             if p == -1 then first_ok (ip+1)
             else let nvert = vert lor (1 lsl p)
                  and ndiag_l = (diag_l lor (1 lsl p)) lsl 1
                  and ndiag_r = (diag_r lor (1 lsl p)) lsr 1 in
                  match f (k+1) nvert ndiag_l ndiag_r (p::acc) with
                  | None -> first_ok (ip+1)
                  | Some res -> Some res
      in
      first_ok 0
    )
  in
  let (Some res) = f 0 0 0 0 [] in
  res

let print_map =
  Array.iter (fun row -> Array.iter (fun x -> print_char (if x then 'X' else '.'))
                                    row;
                         print_newline ())

let _ =
  let map = Array.make_matrix 30 30 false in
  let f1 i j =
    map.(i+1).(j+1) <- true;
    map.(28-i).(28-j) <- true
  in
  List.iteri f1 (gen_n_queens 13);
  let f2 i j =
    map.(i+1).(28-j) <- true;
    map.(28-i).(j+1) <- true
  in
  List.iteri f2 (gen_n_queens 13);
  print_map map
  
