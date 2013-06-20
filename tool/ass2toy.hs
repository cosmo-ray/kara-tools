import Data.List.Split

decompose l = let l2 = splitOn "," l in (((splitOn ":" $ l2!!0)!!0), l2!!1, l2!!9)

toCentisecondes s = let l = splitOn ":" s in let l2 = splitOn "." (l!!2) in let [a,b,c,d] = map (\x -> read x :: Int) [l!!0,l!!1,l2!!0,l2!!1] in d + c * 100 + b * 6000 + a * 360000

lineok l = (splitOn ":" $ (splitOn "," l)!!0)!!0 == "Dialogue"

isnum x = elem x "0123456789"

separe dl3 = let l = map (splitOn "}") (tail $ splitOn "{\\" dl3) in map (\x -> (read (filter isnum $ x!!0) :: Int,x!!1)) l

aux l t = case l of
      []        -> []
      (n,""):xs -> aux xs (t+n)
      (n,z):xs  -> [(t,t+n,z)] ++ (aux xs (t+n))
