data Sentido = Esquerda | Direita | Acima | Abaixo deriving (Show)

type Pos = (Double, Double)

move :: Sentido -> Pos -> Pos
move Esquerda (x,y) = (x-1,y)
move Direita (x,y) = (x+1,y)
move Acima (x,y) = (x ,y+1)
move Abaixo (x,y) = (x ,y-1)

--moves :: [Sentido] -> Pos -> Pos
--moves [] p = p
--moves (s:ss) p = moves ss (move s p)

moves :: [Sentido] -> Pos -> Pos
moves sentidos pontoInicial = foldl (flip move) pontoInicial sentidos

flipSentido :: Sentido -> Sentido
flipSentido Direita = Esquerda
flipSentido Esquerda = Direita
flipSentido Acima = Abaixo
flipSentido Abaixo = Acima

