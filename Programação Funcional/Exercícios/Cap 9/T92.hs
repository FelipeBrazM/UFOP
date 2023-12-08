module Main (main) where

main :: IO ()
main = 
    do  putStrLn "Digite um número: "
        n1 <- readLn
        putStrLn $ "Digite outro número: "
        n2 <- readLn 
        putStrLn $ "Digite outro número: "
        n3 <- readLn :: IO Float
        putStr $ "Produto dos números digitados: "
        putStrLn (show (n1 * n2 * n3))

