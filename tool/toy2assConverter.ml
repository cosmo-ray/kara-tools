open Toy2ass;;
print_endline "start conversion ";;
let lastPoint = String.rindex Sys.argv.(1) '.' ;;
let baseName = String.sub Sys.argv.(1) 0 lastPoint ;;

  writeAssToFile (toy2ass (baseName^".lyr") (baseName^".frm") (float_of_string Sys.argv.(2)))  (baseName^".ass");;

