import System.IO (stdout, hSetBuffering, BufferMode(NoBuffering))

precoRetrato :: Integer -> String -> Double 
precoRetrato numPessoas diaSemana 
    | numPessoas == 1 = precoBase 
    | numPessoas == 2 = precoBase + 30.0
    | numPessoas == 3 = precoBase + 50.0
    | numPessoas == 4 = precoBase + 65.0
    | numPessoas == 5 = precoBase + 75.0
    | numPessoas == 6 = precoBase + 80.0
    | numPessoas >= 7 = precoBase + 85.0
    | otherwise = error "Número de pessoas inválido"
  where
    precoBase = if diaSemana `elem` ["sábado", "domingo"]
                    then 1.2 * 100.0 -- 20% a mais no final de semana 
                    else 100.0

main :: IO ()
main = do
    hSetBuffering stdout NoBuffering
    putStrLn "Bem-vindo ao estúdio Boa Imagem!"
    putStr "Entre com a quantidade de pessoas na foto, e o dia da semana: "
    userInput <- getLine 
    let numPessoas :: Integer 
        numPessoas = read userInput
    diaSemana <- getLine
    putStrLn $ "O valor total é: " ++ show (precoRetrato numPessoas diaSemana)
