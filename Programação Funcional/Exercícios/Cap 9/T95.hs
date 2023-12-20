module Main (main) where
import System.IO(stdout, hSetBuffering, BufferMode(NoBuffering))

calculaEmprestimo :: Double -> Double -> Bool
calculaEmprestimo salario prestacao = 
    if prestacao <= salario * 0.3 then True else False

main :: IO ()
main = 
    do  hSetBuffering stdout NoBuffering
        putStrLn "Análise de crédito"
        putStrLn "-------------------------------------------"
        
        putStr "Salário bruto: "
        salario <- readLn

        putStr "Valor da prestação: "
        prestacao <- readLn

        let sOuN = calculaEmprestimo salario prestacao
        if sOuN == True then putStrLn "O empréstimo pode ser concedido."
        else putStrLn "O empréstimo não pode ser concedido."
