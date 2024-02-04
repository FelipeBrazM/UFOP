data Horario = AM Int Int Int | PM Int Int Int

totalSegundos :: Horario -> Int
totalSegundos (AM h m s) = (h*60 + m)*60 + s
totalSegundos (PM h m s) = ((h+12)*60 + m)*60 + s
