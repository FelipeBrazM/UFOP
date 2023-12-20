module Main (main) where
import System.IO (stdout, hSetBuffering, BufferMode(NoBuffering))

main :: IO ()
main = 
    do  hSetBuffering stdout NoBuffering 
        putStrLn "----------"
        putStrLn "Opções: "
        putStrLn "----------"
        putStrLn "1. Imposto"
        putStrLn "2. Novo salario"
        putStrLn "3. Classificação"
        putStrLn "----------"
        putStr "Digite a opção desejada: "
        op <- readLn
        putStrLn " "
        if op == 1 
            then do putStrLn "Cálculo de Imposto"
                    putStr "Digite o salário: "
                    salário <- readLn
                    let taxa | salário < 500 = 5
                             | salário < 850 = 10 
                             | otherwise = 15 
                        imposto = taxa * salário / 100
                    putStrLn $ "Imposto calculado: " ++ show imposto
        else if op == 2
        then do putStrLn "Cálculo do novo salário"
                putStr "Digite o salário: "
                salário <- readLn 
                let aumento | salário > 1500 = 25
                            | salário >= 750 = 50 
                            | salário >= 450 = 75
                            | otherwise = 100
                    novoSalário = salário + aumento
                putStrLn $ "Novo salário: " ++ show novoSalário
        else if op == 3 
        then do putStrLn "Classificação do salário"
                putStr "Digite o salário: "
                salário <- readLn 
                let classificação | salário <= 750 = "mal remunerado"
                                  | otherwise = "bem remunerado"
                putStrLn $ "Classificação obtida: " ++ classificação
        else putStrLn "Opção invállida!"



