module Main where 

import System.IO (hSetBuffering, stdout, BufferMode(NoBuffering))

main :: IO ()
main = do
    hSetBuffering stdout NoBuffering
    putStr "Digite a nota do trabalho de laboratório: "
    lab <- readLn
    putStr "Digite a nota da avaliação semestral: "
    semestral <- readLn
    putStr "Digite a nota do exame final: "
    final <- readLn
    putStrLn ""
    putStrLn "Conceito obtido: "
    let conceitoObtido = conceito lab semestral final 
    putStrLn [conceitoObtido]

conceito :: Float -> Float -> Float -> Char
conceito lab semestral final 
    | nota < 5.0 = 'E'
    | nota >= 5.0 && nota < 6.0 = 'D'
    | nota >= 6.0 && nota < 7.0 = 'C'
    | nota >= 7.0 && nota < 8.0 = 'B'
    | otherwise = 'A'
  where 
    nota = (lab * 2.0 + semestral * 3.0 + final * 5.0) / 10.0
