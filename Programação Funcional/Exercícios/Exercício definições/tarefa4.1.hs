gravidade :: Double
gravidade = 6.67e-11

forcaGravidade :: Double -> Double -> Double -> Double 
forcaGravidade m1 m2 d = gravidade * m1 * m2 / d^2

