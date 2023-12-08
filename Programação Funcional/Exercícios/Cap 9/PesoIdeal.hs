module Main (main) where

import System.IO (stdout, hSetBuffering, BufferMode(NoBuffering))

main :: IO ()
main = 
    do  hSetBuffering stdout NoBuffering
        putStr "ALtura (m): "
        h <- readLn
        putStr "Sexo (f/m): "
        s <- getLine 
        if s == "F" || s == "f"
            then putStrLn $ "Peso ideal: " ++ show (62.1 * h - 44.7)
            else if s == "M" || s == "m"
                then putStrLn $ "Peso ideal: " ++ show (72.7 * h -58)
                else putStrLn "Sexo inválido"
                