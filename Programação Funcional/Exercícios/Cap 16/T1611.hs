module Main (main) where

import System.IO (stdout, hSetBuffering, BufferMode(NoBuffering))

main :: IO ()
main = do
    hSetBuffering stdout NoBuffering
    putStrLn "Emissão de cupom fiscal v1.0"
    putStrLn "===================================="
    putStrLn ""
    putStrLn "Digite os códigos de barra das mercadorias (0 termina):"
    codigos <- leCodigos
    putStrLn "===================================="
    putStr (fazCompra tabelaMercadorias codigos)
    putStrLn "===================================="

type Nome = String 
type Preco = Int 
type Codigo= Int
type Mercadorias = [(Codigo, Nome, Preco)]
type Carrinho = [Codigo]
type Conta = [(Nome, Preco)]

tabelaMercadorias :: Mercadorias
tabelaMercadorias = [(4719, "Fish Fingers", 121)
                    , (5643, "Nappies", 1010)
                    , (3814, "Orange Jelly", 56)
                    ,(1111, "Hula Hoops", 21)
                    , (1112, "Hula Hoops (Giant)", 133)
                    , (1234, "Dry Sherry, 1lt", 540)
                    ]

formataCentavos :: Preco -> String
formataCentavos preco = show quo ++ "." ++ (if res < 10 then "0" else "") ++ show res
                        where 
                            (quo, res) = divMod preco 100


tamanhoLinha :: Int
tamanhoLinha = 30

formataLinha :: (Nome, Preco) -> String
formataLinha (nome, preco) = nome ++
    replicate qtdepts '.' ++
    precoStr ++
    "\n"
  where
    precoStr = formataCentavos preco
    qtdepts = tamanhoLinha - length nome - length precoStr

formataLinhas :: [(Nome, Preco)] -> String
formataLinhas itens = foldl (++) "" (map formataLinha itens)

formataTotal :: Preco -> String
formataTotal preco = "\nTotal" ++ (replicate qtdepts '.') ++ precoStr
                where
                    precoStr = formataCentavos preco
                    qtdepts = tamanhoLinha - length "Total" - length precoStr

calculaTotal :: Conta -> Preco
calculaTotal itens = sum (map snd itens)

formataConta :: Conta -> String
formataConta itens = "Haskell Store\n" ++ "\n" ++ formataLinhas itens ++ formataTotal (calculaTotal itens)

procuraCodigo :: Mercadorias -> Codigo -> (Nome, Preco)
procuraCodigo [] _ = ("Unknown item", 0)
procuraCodigo ((cod1,nome,preco):resto) cod2 | cod1 == cod2 = (nome,preco)
                                             | otherwise = procuraCodigo resto cod2

criaConta :: Mercadorias -> Carrinho -> Conta
criaConta tabela itens = map (procuraCodigo tabela) itens

fazCompra :: Mercadorias -> Carrinho -> String
fazCompra tabela itens = formataConta (criaConta tabela itens)

leCodigos :: IO [Codigo]
leCodigos = do
    x <- readLn
    if x == 0 
        then return []
        else do
            xs <- leCodigos
            return (x : xs)


