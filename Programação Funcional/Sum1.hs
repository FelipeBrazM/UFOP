module Main (main) where

import System.IO (stdout, hSetBuffering, BufferMode(NoBuffering))

main :: IO ()
main = do 
        hSetBuffering stdout NoBuffering -- desabilita a buferrização 
        putStr "Quantidade de números: "
        num <- readLn
        soma <- readInput num  
        putStr "Soma dos números: " 
        print soma

readInput :: Integer -> IO Integer
readInput num | num <= 0 = return 0
              | num > 0 = do 
                            putStr "Digite um número: " 
                            x <- readLn
                            soma <- readInput (num-1)
                            return (x + soma)                


