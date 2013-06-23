import Data.List.Split
import System.IO

decompose l = let l2 = splitOn "," l in (((splitOn ":" $ l2!!0)!!0), l2!!1, foldr (++) "" (drop 9 l2))

toCentisecondes s = let l = splitOn ":" s in let l2 = splitOn "." (l!!2) in let [a,b,c,d] = map (\x -> read x :: Int) [l!!0,l!!1,l2!!0,l2!!1] in d + c * 100 + b * 6000 + a * 360000

lineok l = (splitOn ":" $ (splitOn "," l)!!0)!!0 == "Dialogue"

isnum x = elem x "0123456789"

separe dl3 = let l = map (splitOn "}") (tail $ splitOn "{\\" dl3) in map (\x -> (read (filter isnum $ x!!0) :: Int,x!!1)) l

aux l t = case l of
      []        -> []
      (n,""):xs -> aux xs (t+n)
      (n,z):xs  -> [(t,t+n,z)] ++ (aux xs (t+n))

extractlyr p = foldr (\(u,v,x) -> \y -> "&" ++ x ++ y) "" p

extractfrm p = foldr (\(u,v,x) -> \y -> show u ++ " " ++ show v ++ "\n" ++ y) "" p

extractboth p = foldr (\(u,v,x) -> \(y,z) -> (("&" ++ x ++ y),(show u ++ " " ++ show v ++ "\n" ++ z))) ("","") p

main0 s = let (a,b,c) = decompose s in let t = toCentisecondes b in let e = separe c in let p = aux e t in p

main :: IO ()
main = do 
       inh <- openFile "b.ass" ReadMode
       outh <- openFile "output.txt" WriteMode
       outh2 <- openFile "output2.txt" WriteMode
       mainloop inh outh outh2
       hClose inh
       hClose outh
       hClose outh2


mainloop :: Handle -> Handle -> Handle -> IO ()
mainloop inh outh outh2 = 
    do ineof <- hIsEOF inh
       if ineof
           then return ()
           else do p <- fmap main0 (hGetLine inh)
                   let (p1,p2) = extractboth p
                   hPutStrLn outh (init p2)
                   hPutStrLn outh2 (p1)
                   mainloop inh outh outh2


