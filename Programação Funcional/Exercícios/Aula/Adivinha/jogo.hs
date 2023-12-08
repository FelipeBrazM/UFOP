module Main where

import System.IO (stdout, hSetBuffering, BufferMode(NoBuffering))
import Data.Char (toUpper)
import System.Random (randomRIO)
import Control.Monad (when)

main :: IO ()
main = 
    do  hSetBuffering stdout NoBuffering
        putStrLn "Adivinha o número v1.0"
        putStrLn "========================================="
        jogar

simOuNao :: String -> IO Bool
simOuNao pergunta =
    do  putStr pergunta
        resposta <- getLine
        case map toUpper resposta of
            "S" -> return True
            "N" -> return False
            _ -> do putStrLn " RESPOSTA INVÁLIDA"
                    simOuNao pergunta

acertar :: Integer -> IO ()
acertar secreto =
    do  putStr "Digite um número entre 1 e 1000: "
        x <- readLn
        if x == secreto
        then putStrLn "Parabéns, você acertou"
        else do putStrLn (if x < secreto then "Muito pequeno" else "Muito grande")
                putStrLn "Tente novamente\n"
                acertar secreto

jogar :: IO ()
jogar =
    do  num <- randomRIO (1, 1000)
        acertar num
        resposta <- simOuNao "Deseja jogar novamente?"
        when resposta jogar