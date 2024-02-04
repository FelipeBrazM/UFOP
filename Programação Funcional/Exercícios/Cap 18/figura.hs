data Figura = Circulo Double | Retangulo Double Double deriving Show

eRedondo :: Figura -> Bool
eRedondo (Circulo _) = True
eRedondo (Retangulo _ _) = False

area :: Figura -> Double
area (Circulo r) = pi * r^2
area (Retangulo b a) = b * a

quadrado :: Double -> Figura 
quadrado lado = Retangulo lado lado