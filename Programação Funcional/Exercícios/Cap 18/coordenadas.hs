data Coord = Coord Double Double deriving (Show)

somaVet :: Coord -> Coord -> Coord
somaVet (Coord x1 y1) (Coord x2 y2) = Coord (x1 + x2) (y1 + y2)
