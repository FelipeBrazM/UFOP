-- Adicionamos um módulo para as definições
module MyListModule where

data MyList a = EmptyList | Cons a (MyList a) deriving Show

instance Functor MyList where
  fmap _ EmptyList        = EmptyList
  fmap f (Cons x myList)  = Cons (f x) (fmap f myList)
