data Cor = Azul | Amarelo | Verde | Vermelho 

fria :: Cor -> Bool
fria Azul = True
fria Verde = True
fria _ = False

quente :: Cor -> Bool
quente Amarelo = True
quente Vermelho = True
quente _ = False

