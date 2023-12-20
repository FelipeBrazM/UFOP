module Main (main) where 
import System.IO (stdout, hSetBuffering, BufferMode(NoBuffering))

soma :: Integer -> Integer -> Integer
soma m n 
    | m == 0 = n
    | otherwise = soma (pred m) (succ n)

main :: IO ()
main = 
    do  hSetBuffering stdout NoBuffering 
        putStr "Entre com os dois números naturais para somar: "
        m  <- readLn 
        n <- readLn

        let retorno = soma m n
        putStrLn $ "A soma de " ++ show m ++ " e " ++ show n ++ " é: " ++ show retorno