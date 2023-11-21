module Main (main) where

import System.IO (stdout, hSetBuffering, BufferMode(NoBuffering))

main :: IO ()
main = do 
        total <- pdois 5 1
        putStrLn total

pdois :: Int -> Int -> IO String
pdois n y 
    | n == 0 = return (show y)
    | n > 0 = pdois (n-1) (2*y)
