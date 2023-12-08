module Main where

import Valor (valorTotal)

import System.IO (stdout, hSetBuffering, BufferMode(NoBuffering))

main :: IO ()
main = do 
    hSetBuffering stdout NoBuffering -- desabilita a bufferização
    putStr "Digite a quantidade de Morangos (em Kg): "
    pesoMorango <- readLn
    putStr "Digite a quantidade de Maçãs (em Kg): "
    pesoMaca <- readLn

    if pesoMorango < 0 || pesoMaca < 0
      then putStrLn "Entrada inválida"
      else putStrLn ("O valor total da compra é R$ " ++ show (valorTotal pesoMorango pesoMaca))



  
