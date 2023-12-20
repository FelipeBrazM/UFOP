module Main (main) where 
import System.IO (stdout, hSetBuffering, BufferMode(NoBuffering))

-- Função para calcular o fatorial duplo de um número natural n
fatorialDuplo :: Integer -> Integer
fatorialDuplo n 
    | n == 0 || n == 1 = 1 -- Caso base: fatorial duplo de 0 ou 1 é 1
    | otherwise = n * fatorialDuplo (n - 2) --Caso recursivo: multiplicar por (n - 2) e chamar recursivamente


main :: IO ()
main = 
    do  hSetBuffering stdout NoBuffering 
        putStrLn "Calculadora de Fatorial Duplo"
        putStr "Entre com o valor de N: "
        n <- readLn

        let retorno = fatorialDuplo n
        putStrLn $ "O fatorial duplo de " ++ show n ++ " é: " ++ show retorno

