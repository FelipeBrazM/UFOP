data Figura = Circulo Double | Retangulo Double Double deriving Show

calculaPeri :: Figura -> Double 
calculaPeri (Circulo r) = 2 * pi * r
calculaPeri (Retangulo a b) = 2 * a + 2 * b
