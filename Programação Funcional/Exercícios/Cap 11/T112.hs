module Main (main) where
import System.IO (stdout, hSetBuffering, BufferMode(NoBuffering))

main :: IO ()
main = do
    hSetBuffering stdout NoBuffering
    putStrLn "Cálculo da média aritmética"
    putStrLn "---------------------------------------"
    putStrLn "Digite uma sequência de números (um por linha)"
    putStrLn "Para terminar digite um valor negativo"

    lista <- lerLista
    case lista of 
        []  -> putStrLn "Sequência vazia"
        _   -> do putStr "A média dos números digitados é: "
                  print (sum lista / fromIntegral (length lista))


lerLista =  do  x <- readLn
                if x < 0 
                then return []
                else do xs <- lerLista 
                        return (x:xs)
