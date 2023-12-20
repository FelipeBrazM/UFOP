module Main (main) where 
import System.IO (stdout, hSetBuffering, BufferMode(NoBuffering))

multiIntervalo :: Integer -> Integer -> Integer
multiIntervalo m n 
    | m == n = m
    | otherwise = m * multiIntervalo (m + 1) n

main :: IO ()
main = 
    do  hSetBuffering stdout NoBuffering 
        putStrLn "Calcula multiplicação em um intervalo"
        putStr "Entre com o valor de M e N: "
        m <- readLn
        n <- readLn

        let retorno = multiIntervalo m n
        putStrLn $ "O produto dos números no intervalo de " ++ show m ++ " até " ++ show n ++ " é: " ++ show retorno

