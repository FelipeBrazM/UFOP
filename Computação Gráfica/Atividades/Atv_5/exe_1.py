import pygame
import numpy as np

# Inicializar o pygame
pygame.init()

# Configuração da tela
width, height = 800, 600
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption("Triângulo com Gradiente")

# Definir os vértices do triângulo e suas cores
vertex1 = (200, 100)  # Vermelho
color1 = (255, 0, 0)

vertex2 = (600, 100)  # Verde
color2 = (0, 255, 0)

vertex3 = (400, 500)  # Azul
color3 = (0, 0, 255)

# Função para interpolar cores
def interpolate_color(color_a, color_b, t):
    return tuple(int(color_a[i] + (color_b[i] - color_a[i]) * t) for i in range(3))

# Função para desenhar o triângulo com gradiente
def draw_gradient_triangle(screen, v1, v2, v3, c1, c2, c3):
    # Ordenar os vértices por coordenada y
    vertices = sorted([(v1, c1), (v2, c2), (v3, c3)], key=lambda v: v[0][1])
    (x1, y1), col1 = vertices[0]
    (x2, y2), col2 = vertices[1]
    (x3, y3), col3 = vertices[2]

    for y in range(y1, y3 + 1):
        if y < y2:
            t1 = (y - y1) / (y2 - y1) if y2 != y1 else 0
            t2 = (y - y1) / (y3 - y1) if y3 != y1 else 0
            x_start = int(x1 + (x2 - x1) * t1)
            x_end = int(x1 + (x3 - x1) * t2)
            c_start = interpolate_color(col1, col2, t1)
            c_end = interpolate_color(col1, col3, t2)
        else:
            t1 = (y - y2) / (y3 - y2) if y3 != y2 else 0
            t2 = (y - y1) / (y3 - y1) if y3 != y1 else 0
            x_start = int(x2 + (x3 - x2) * t1)
            x_end = int(x1 + (x3 - x1) * t2)
            c_start = interpolate_color(col2, col3, t1)
            c_end = interpolate_color(col1, col3, t2)

        if x_start > x_end:
            x_start, x_end = x_end, x_start
            c_start, c_end = c_end, c_start

        for x in range(x_start, x_end + 1):
            t = (x - x_start) / (x_end - x_start) if x_end != x_start else 0
            color = interpolate_color(c_start, c_end, t)
            screen.set_at((x, y), color)

# Loop principal
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Preencher o fundo
    screen.fill((0, 0, 0))

    # Desenhar o triângulo com gradiente
    draw_gradient_triangle(screen, vertex1, vertex2, vertex3, color1, color2, color3)

    # Atualizar a tela
    pygame.display.flip()

# Encerrar o pygame
pygame.quit()
