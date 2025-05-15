# Exercício 1 

import matplotlib.pyplot as plt

# Valores constantes para G e B
g = 100
b = 150

# Lista para armazenar as cores do gradiente
gradient = []

# Gerando o gradiente RGB
for r in range(256):  # R varia de 0 a 255
    gradient.append((r, g, b))

# Exibindo o gradiente como uma imagem
plt.imshow([gradient], aspect='auto')
plt.axis('off')  # Remove os eixos
plt.show()
