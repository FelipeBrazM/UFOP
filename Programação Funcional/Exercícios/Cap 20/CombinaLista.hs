combineLists :: [a] -> [b] -> [(a, b)]
combineLists xs ys = (,) <$> xs <*> ys


