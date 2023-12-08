module Main where
import System.IO (stdout, hSetBuffering, BufferMode(NoBuffering))

main :: IO ()
main = do
    hSetBuffering stdout NoBuffering
    putStr "Digite uma frase: "
    frase <- getLine

    let fraseReversa = reverse frase

    if fraseReversa == frase
        then putStrLn "É um palíndrome!"
        else putStrLn "Não é um palíndrome!"
