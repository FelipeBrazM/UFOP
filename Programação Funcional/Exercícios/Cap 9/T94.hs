module Main (main) where
import System.IO (stdout, hSetBuffering, BufferMode (NoBuffering))

celsius :: Double -> Double 
celsius f = 5/9 * (f - 32)

main :: IO ()
main = 
    do  hSetBuffering stdout NoBuffering
        putStr "Temperatura em Fahrenheit: "
        f <- readLn

        putStrLn $ "Temperatura em Celsius: " ++ show (celsius f)

