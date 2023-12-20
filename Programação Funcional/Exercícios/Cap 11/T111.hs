module Main (main) where 
import System.IO (stdout, hSetBuffering, BufferMode(NoBuffering))

soma :: Integer -> Integer -> IO Integer
soma n s | n <= 0 = return s
         | n > 0 = do putStr "Digite um número: "
                      x <- readLn 
                      soma (n-1) (x+s)

main :: IO ()
main = 
    do  hSetBuffering stdout NoBuffering 
        putStr "Quantidade de números: "
        n <- readLn

        retorno <- soma n 0
        putStrLn $ "Soma dos números digitados: " ++ show retorno