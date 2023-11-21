module Main (main) where

import System.IO (stdout, hSetBuffering, BufferMode(NoBuffering))

main :: IO ()
main = do 
        hSetBuffering stdout NoBuffering -- desabilita a buferrização 
        putStr "Quantidade de números: "
        num <- readLn
        soma <- readInput num 0 
        putStr "Soma dos números: " 
        print soma

readInput num soma | num <= 0 = return soma
                   | num > 0 = do 
                                putStr "Digite um número: " 
                                x <- readLn
                                readInput (num - 1) (x + soma)                


