-- Definindo uma instância de Functor para Tree
data Tree a = Leaf a | Node (Tree a) (Tree a) deriving Show

instance Functor Tree where
    fmap f (Leaf a)     = Leaf (f a)
    fmap f (Node left right) = Node (fmap f left) (fmap f right)