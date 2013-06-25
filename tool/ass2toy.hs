import Data.List.Split
import System.IO
import Text.Regex.Posix
import System.Environment
import Filesystem.Path
import Filesystem.Path.CurrentOS
import Data.Text (pack)

modifext s e = let fp = decodeString s in let nfp = replaceExtension fp (Data.Text.pack e) in encodeString nfp

m = "[0-9a-zA-Z ]*"

matchregex s = s =~ ("^Dialogue: [0-9]*,[0-9]*:[0-9]*:[0-9]*.[0-9]*,[0-9]*:[0-9]*:[0-9]*.[0-9]*,"++m++","++m++",[0-9]*,[0-9]*,[0-9]*,"++m++",") :: String

decompose l = let a = matchregex l in if a == [] then (False, [], []) else let l2 = splitOn "," a in (True, l2!!1, drop (length a) l)

toCentisecondes s = let l = splitOn ":" s in let l2 = splitOn "." (l!!2) in let [a,b,c,d] = map (\x -> read x :: Int) [l!!0,l!!1,l2!!0,l2!!1] in d + c * 100 + b * 6000 + a * 360000

isnum x = elem x "0123456789"

separe dl3 = let l = map (splitOn "}") (tail $ splitOn "{\\" dl3) in map (\x -> (read (filter isnum $ x!!0) :: Int,x!!1)) l

aux l t = case l of
      []        -> []
      (n,""):xs -> aux xs (t+n)
      (n,z):xs  -> [(t,t+n,z)] ++ (aux xs (t+n))

conv :: Float -> Int -> Int
conv fps x = let y = (fromIntegral x) in floor (0.5+y*fps/100)

extractboth fps p = foldr (\(u,v,x) -> \(y,z) -> (("&" ++ x ++ y),(show (conv fps u) ++ " " ++ show (conv fps v) ++ "\n" ++ z))) ("","") p

main1 s = let (a,b,c) = decompose s in if a then let t = toCentisecondes b in let e = separe c in let p = aux e t in Just p else Nothing

main :: IO ()
main = do 
       args <- getArgs
       case args of
             x:y:[]-> do
                      inh <- openFile x ReadMode
                      outh <- openFile (modifext x "frm") WriteMode
                      outh2 <- openFile (modifext x "lyr") WriteMode
                      mainloop inh outh outh2 (read y :: Float)
                      hClose inh
                      hClose outh
                      hClose outh2
             _ -> putStrLn "Please specify an input file name and a fps"

mainloop ::  Handle -> Handle -> Handle -> Float -> IO ()
mainloop inh outh outh2 fps = 
    do ineof <- hIsEOF inh
       if ineof
           then return ()
           else do p <- fmap main1 (hGetLine inh)
                   case p of
                        Just r ->let (p1,p2) = extractboth fps r in do
                                     hPutStrLn outh (init p2)
                                     hPutStrLn outh2 (p1)
                        Nothing -> return ()
                   mainloop inh outh outh2 fps


