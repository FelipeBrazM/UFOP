module Main (main) where
import System.IO (stdout, hSetBuffering, BufferMode(NoBuffering))

calculaAumento :: Double -> Integer -> Integer -> Double
calculaAumento salario anos contador
    | anos == 0 = salario
    | contador == 1 = calculaAumento (1.015 * salario) (anos - 1) (contador + 1)
    | otherwise = calculaAumento (1.015 * (fromIntegral contador)^2 * salario) (anos - 1) (contador + 1)

main :: IO ()
main = do
    hSetBuffering stdout NoBuffering
    putStrLn "Calcula aumento"
    putStr "Digite o valor do seu salário inicial: "
    salario <- readLn 
    putStr "Quantos anos na empresa: "
    anos <- readLn

    let retorno = calculaAumento salario anos 1
    putStrLn $ "Em " ++ show anos ++ " anos, o salário foi de " ++ show salario ++ " para: " ++ show retorno
