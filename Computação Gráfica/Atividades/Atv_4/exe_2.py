# Exercício 2

import colorsys

def rgb_to_hsv(r, g, b):
    # Normaliza os valores RGB para o intervalo [0, 1]
    r, g, b = r / 255.0, g / 255.0, b / 255.0
    
    # Converte RGB para HSV
    h, s, v = colorsys.rgb_to_hsv(r, g, b)
    
    # Converte os valores de volta para o intervalo [0, 255] para o valor V
    return (h * 360, s * 100, v * 100)

# Entrada de valores RGB
r = int(input("Digite o valor de R (0-255): "))
g = int(input("Digite o valor de G (0-255): "))
b = int(input("Digite o valor de B (0-255): "))

# Converte RGB para HSV
hsv = rgb_to_hsv(r, g, b)

# Exibe o resultado
print(f"HSV: H={hsv[0]:.2f}, S={hsv[1]:.2f}, V={hsv[2]:.2f}")
