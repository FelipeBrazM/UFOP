module Main (main) where 
import System.IO (stdout, hSetBuffering, BufferMode(NoBuffering))

prompt msg = do putStr msg
                readLn

main = 
    do  hSetBuffering stdout NoBuffering 
        n1 <- prompt "Nota 1: "
        n2 <- prompt "Nota 2: "
        n3 <- prompt "Nota 3: "
        let media = (n1 + n2 + n3)/3 
        putStrLn $ "Media: " ++ show media
        putStrLn "Situação: "
        if media < 3
            then putStrLn "Reprovado"
            else if media < 7 
                then putStrLn "Exame especial"
                else putStrLn "Aprovado"