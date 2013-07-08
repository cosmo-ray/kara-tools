(* enleve les \013 Ela fin *)
let clean_end s = if s.[String.length s - 1]='\013' then String.sub s 0 (String.length s - 1) else s;;

(* convertit un string en liste de char *)
let rec list_string s = if s = "" then [] else s.[0]::(list_string (String.sub s 1 (String.length s - 1)));;

(* compte le nombre d'occurences d'un char c dans un string s *)
let rec countocc c s = let l = list_string s in List.length (List.filter (fun x->x=c) l);;

(* place X syllabe par phrase *)
let rec gs s i = let t = String.sub s 1 (String.length s - 1) in if String.contains t '&' then
let a = String.index t '&' in
(i,(String.sub t 0 a))::(gs (String.sub t a (String.length t - a)) (i+a))
else [i,t];;

let gsyl s = gs s 0;;

(* frames => couple d'entiers *)
let local s = let t = clean_end s in let i = String.index s ' ' in (int_of_string (String.sub t 0 i),int_of_string (String.sub t (i+1) (String.length t - i -1)));;

(* fichier => liste de strings *)
let list_file s = let a = open_in s in
let rec lister () = try
	let t = input_line a in t::lister()
	with _ -> close_in a;[] in lister ();;

(* compte les syllabes dans une phrase *)
let countsyl s = let l = List.filter (fun x->x='&') (list_string s) in List.length l;;	

(* separe les n premiers éléments du reste d'une liste *)
let rec cutn l n = match (n,l) with
	|(0,_)->[],l
	|(x,y::q)->let (a,b) = cutn q (x-1) in (y::a,b);;
	
(* efface les eventuelles lignes vides *)
let clean_void l = List.filter (fun x->x<>"") l;;
	
(* premier decoupage *)
(* f1 : fichier lyrics *)
(* f2 : fichier frm *)
let blob f1 f2 =
	let lf = List.map local (clean_void (list_file f2)) in
	let lp = List.map clean_end (clean_void (list_file f1)) in
	lf,lp;;


(* dernier element d'une liste *)
let rec last = function
|x::[]->x
|x::q->last q
|_->failwith "Liste vide ou autre";;

(* premiere organisation *)
(* old = let truc f1 f2 = let (a,b) = blob f1 f2 in let rec aux1 l1 (x::q) = let n = countsyl x in let (c,d) = cutn l1 n in if d = [] then [c,x] else (c,x)::(aux1 d q) in aux1 a b;; *)
let truc f1 f2 = let (a,b) = blob f1 f2 in
let rec aux1 l1 (x::q) = let n = countsyl x in
	let (c,d) = cutn l1 n in
	if d = [] then [c,gsyl x] else (c,gsyl x)::(aux1 d q) in aux1 a b;;

let bettertruc f1 f2 = let l = truc f1 f2 in List.map (fun (x,y)->List.combine x y) l;;


(* negation qui reste dans les entiers naturels *)
let negnat a x = let b = a-x in max b 0;;

(* mikomi : the customisation *)
let treatsent l = let (a,_),(_,_) = List.hd l and (_,b),(u,v) = last l in (negnat a 35,negnat a 25,a,b,b+10,u+String.length v,l);;

let datruc f1 f2 = List.map treatsent (bettertruc f1 f2);;

let firstnonoqp l = let rec aux m n =
	if List.mem n m then aux m (n+1) else n in aux l 0;;

let mapun l = List.map (function (a,_,_,_,b,_,_)->(a,b)) l;;

let bonpos l = let rec auxi r c z = match z with
	|(a,b)::q->let l = List.filter (fun (x,y,z)->a<y) c in let l2 = List.map (fun (x,y,z)->z) l in
	let pos = firstnonoqp l2 in auxi (pos::r) ((a,b,pos)::l) q
	|[]->List.rev r in auxi [] [] l;;

(* zetruc contient toutes les informations *)
let zetruc f1 f2 = let l = datruc f1 f2 in let l2 = bonpos (mapun l) in
List.combine l l2;; 

(* affiche plusieurs espaces *)
let espaces n = String.make n ' ';;

let sauts n = String.make (2*n) '|';;

(* affichage d'une syllabe : liste de strings *)
let affsyl (a,b,_,d,e,f,g) ((x,y),(z,t)) =
["{"^(string_of_int a)^"}{"^(string_of_int b)^"}"^(sauts f)^"{c:$0000FF80:$FF00FF80}"^(espaces z)^t^(espaces (g-z-String.length t))^"\n";
"{"^(string_of_int b)^"}{"^(string_of_int x)^"}"^(sauts f)^"{c:$FF00FF80:$FF00FFFF}"^(espaces z)^t^(espaces (g-z-String.length t))^"\n";
"{"^(string_of_int x)^"}{"^(string_of_int y)^"}"^(sauts f)^"{c:$FF8000FF:$FF0000FF}"^(espaces z)^t^(espaces (g-z-String.length t))^"\n";
"{"^(string_of_int y)^"}{"^(string_of_int d)^"}"^(sauts f)^"{c:$FFFFFF00:$90FF8000}"^(espaces z)^t^(espaces (g-z-String.length t))^"\n";
"{"^(string_of_int d)^"}{"^(string_of_int e)^"}"^(sauts f)^"{c:$90FF8000:$00FF8000}"^(espaces z)^t^(espaces (g-z-String.length t))^"\n";
"{"^(string_of_int x)^"}{"^(string_of_int y)^"}"^(sauts f)^"|"^(espaces z)^"ÿ"^(espaces (g-z-1))^"\n"];;


(* affichage d'une phrase : liste de strings *)
let affsent ((a,b,c,d,e,g,l),f) = List.flatten (List.map (fun x->affsyl (a,b,c,d,e,f,g) x) l);;

(* affichage des lyrics : liste de strings *)
(* lyr étant le résultat de zetruc *)
let afflyr lyr = List.flatten (List.map affsent lyr);;

let read fi = let file = open_in fi in let lines = ref [] in
try
  while true; do
    lines := input_line file :: !lines
  done; []
with End_of_file ->
  close_in file;
  List.rev !lines;;

(* ecriture des paroles dans un fichier *)
let writelyr lyr f llyr= let l = afflyr lyr in
let a = open_out f in let paroles = read llyr in let time = List.flatten (List.map (fun (_,_,_,_,_,_,l)->l) (List.map (fun (x,y)->x) lyr)) in output_string a "# --- This is a generated file --- -*- KyonataGenerator > -*-\n";output_string a "{0}{0}{needed at beginning of file for file format recognition by mplayer}\n";output_string a "# --- LYRICS - GENERATE AGAIN AFTER YOU EDIT ---\n";output_string a "--%style neo-mikomi\n";List.iter (fun x->output_string a (x^"\n")) paroles;
output_string a "# --- SUB - DO NOT EDIT HERE - MODIFICATIONS WILL BE LOST ---\n";
List.iter (fun x->output_string a x) l;output_string a "# --- TIMING - GENERATE AGAIN AFTER YOU EDIT ---\n";List.iter (fun ((x,y),(z,t))->output_string a ("=="^t^"\n");output_string a ("=="^(string_of_int x)^" "^(string_of_int y)^"\n")) time;close_out a;;


let main () = let a = Sys.argv.(1) in let b = String.sub a 0 (String.length a - 4) in let fichierlyr = b^".lyr" and fichierfrm = b^".frm" in writelyr(zetruc fichierlyr fichierfrm) (b^".txt") fichierlyr;;


main();;
