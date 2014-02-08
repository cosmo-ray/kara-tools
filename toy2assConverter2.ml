open Toy2ass;;
print_endline "start conversion ";;
let lastPoint = String.rindex Sys.argv.(1) '.' ;;
let lastPoint2 = String.rindex Sys.argv.(2) '.' ;;
let baseName = String.sub Sys.argv.(1) 0 lastPoint ;;
let baseName2 = String.sub Sys.argv.(2) 0 lastPoint2 ;;

writeAssToFile (toy2ass (baseName^".lyr") (baseName^".frm") (float_of_string Sys.argv.(3)))  (baseName2^".ass");;

