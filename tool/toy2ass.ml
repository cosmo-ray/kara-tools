let lfrm = [12,21;22,36;38,43;44,48;50,55;57,62;63,73;74,86;87,103];;
let llyr = ["too";"ku ";"ki";"ra";"me";"ku ";"ho";"shi ";"ni"];;
let fps = 23.976;;

let frametocs frame fps = int_of_float(float_of_int(frame) *. 100. /. fps);;

let lfrmtolcs l fps = List.map (fun (x,y)->frametocs x fps,frametocs y fps) l;;

let listesecondes = lfrmtolcs lfrm;;

let extractinfo l =
  let sta,_ = List.hd l and _,fin = List.hd (List.rev l) in
  let l1 = List.map fst l in 
  let rec aux l = match l with
    |x::y::q->(y-x)::aux (y::q)
    |x::[]->[fin-x]
    |_->failwith "extractinfo liste vide" in
  sta,fin,List.rev (aux l1)
;;

let syllabe d s = "{\\k"^string_of_int(d)^"}"^s;;

let sur2 n = (if n<10 then "0" else "")^string_of_int(n);;
let inttohour n = let cs = n mod 100 in let tts = n/100 in let s = tts mod 60 in let ttm = tts / 60 in let h = ttm / 60 in let m = ttm mod 60 in
   string_of_int(h)^":"^sur2 m^":"^sur2 s^"."^sur2 cs;;

let phrase2string lfrm llyr fps = 
  let aux lyr oth = let l = List.combine lyr oth in List.fold_left (fun a->fun (b,c)->a^(syllabe c b)) "" l in
  let sta,fin,oth = extractinfo (lfrmtolcs lfrm fps) in
  "Dialogue: 0,"^inttohour sta^","^inttohour fin^",Default,,0,0,0,,"^aux llyr oth
;;


