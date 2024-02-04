applyFunctions :: [a -> b] -> [a] -> [b]
applyFunctions fs xs = fmap (\f -> fmap f xs) fs >>= id


-- Definindo algumas funções de exemplo
double :: Int -> Int
double x = 2 * x

square :: Int -> Int
square x = x^2