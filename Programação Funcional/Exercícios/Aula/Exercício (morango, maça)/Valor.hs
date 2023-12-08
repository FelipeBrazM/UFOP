module Valor where

valorTotal :: Double -> Double -> Double
valorTotal morangos macas
  | morangos <= 5 && macas <= 5 = (8.50 * morangos) + (5.25 * macas)
  | morangos <= 5                = (8.50 * morangos) + (4.75 * macas)
  | macas <= 5                   = (7.20 * morangos) + (5.25 * macas)
  | otherwise                    = (7.20 * morangos) + (4.75 * macas)
