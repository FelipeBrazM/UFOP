module Main (main) where 
import System.IO (stdout, hSetBuffering, BufferMode(NoBuffering))

calculaPotencia :: Integer -> Integer -> Integer
calculaPotencia x n 
    | n == 0 = 1
    | otherwise = x * calculaPotencia (x) (n - 1)

main :: IO ()
main = 
    do  hSetBuffering stdout NoBuffering 
        putStrLn "Calcula potência"
        putStr "Entre com o valor de x e de n: "
        x <- readLn 
        n <- readLn

        let retorno = calculaPotencia x n  
        putStrLn $ "A potência de: " ++ show x ++ " elevado a " ++ show n ++ " é: " ++ show retorno