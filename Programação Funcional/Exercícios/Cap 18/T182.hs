data ShopItem = Item String Int Double
valorCompra :: [ShopItem] -> Double
valorCompra = sum . (map (\(Item _ qtde preco) -> qtde * preco))