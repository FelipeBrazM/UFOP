module Main (main) where
import System.IO (stdout, hSetBuffering, BufferMode(NoBuffering))

calculaEleitor :: Int -> String
calculaEleitor idade =
    if idade < 16 then "Não eleitor"
    else if idade >= 18 && idade <= 65 then "Eleitor obrigatório"
    else "Eleitor facultativo"

main :: IO ()
main =
    do  hSetBuffering stdout NoBuffering
        putStrLn "Classe Eleitoral"
        putStrLn "-------------------------------------------"

        putStr "Digite a idade da pessoa: "
        idade <- readLn

        let classeEleitor = calculaEleitor idade
        putStrLn classeEleitor
