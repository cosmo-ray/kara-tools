type wave = Voy of char | Cons of char | Break | Vide of char;;

let rec stringtochar s = if s = "" then [] else 
(s.[0])::(stringtochar (String.sub s 1 
(String.length s - 1)));;
let isvoy x = x == 'a' || x=='e' || x=='i' || 
x=='o' || x=='u';;
let iscons x = not(isvoy x) && Char.code x>96 && Char.code x<123;;
let pasmaj s = String.compare s (String.lowercase 
s) ==0;;
let rec updatemot x = match x with
	|a::[]->[a]
	|Vide(x)::q->Vide(x)::(updatemot q)
	|Voy(a)::Vide(b)::q->Voy(a)::updatemot 
(Vide(b)::q)
	|Voy(a)::b::q->Voy(a)::Break::updatemot 
(b::q)
	|Cons(a)::Cons(b)::q->if a=b || a='n' then 
Cons(a)::Break::updatemot (Cons(b)::q)
		else Cons(a)::(updatemot (Cons 
b::q))
	|Cons(a)::b::q->Cons(a)::(updatemot 
(b::q))
	|[]->failwith "mot vide"
	|Break::_->failwith "impossible"
;;
let f1 x = if isvoy x then Voy(x) else if iscons x then Cons(x) else Vide(x);;
let main s = updatemot (List.map f1 (stringtochar 
s));;

let aux1 l = let rec aux l r a = match l with
	|[]->List.rev ((List.rev a)::r)
	|Break::q->aux q ((List.rev a)::r) []
	|x::q->aux q r (x::a) in aux l [] [];;

let f2 = function Cons(x)->Char.escaped x|Voy(x)->Char.escaped x|Vide(x)->Char.escaped x|Break->failwith "erreur Break";;
let f3 l = List.map f2 l;;
let f4 l = List.map (fun x->"&"^String.concat "" 
(f3 x)) l;;
let f5 l = String.concat "" l;;
let main2 x = f5 (f4 (aux1 (main x)));;

let cut2 s c = let a = String.index s c in 
String.sub s 0 a,String.sub s (a+1) (String.length 
s - a - 1);;
let cuttout s c = let rec aux s r = try let (a,b)
=cut2 s c in aux b (a::r) with _->s::r in 
List.rev(aux s []);;
let cutphrase s = cuttout s ' ';;

let main3 s = String.concat " " (List.map main2 
(cutphrase s));;

let file2list f = let r = ref [] in let a = 
open_in f in let _ = try while true do r:=
(input_line a)::(!r) done with _->close_in a in 
List.rev (!r);;

let main4 f = List.map main3 (file2list f);;

let writefile f l = let a = open_out f in 
List.iter (fun x->output_string a (x^"\n")) 
l;close_out a;;

let main5 f1 f2 = writefile f2 (main4 f1);;
let main6 () = let lastPoint = String.rindex 
Sys.argv.(1) '.' in let baseName = String.sub 
Sys.argv.(1) 0 lastPoint in main5 (Sys.argv.(1)) 
(baseName^".lyr");;

let main7 f = List.iter (print_endline) (main4 
f);;
let main8 () = let lastPoint = String.rindex 
Sys.argv.(1) '.' in let baseName = String.sub 
Sys.argv.(1) 0 lastPoint in main7 (Sys.argv.(1));;

main8 ();;
