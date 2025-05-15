import pygame
from pygame.locals import *

# Inicializa o pygame
pygame.init()

# Configurações da tela
WIDTH, HEIGHT = 800, 600
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Aplicação Gráfica com Pygame")

# Configurações do círculo
circle_radius = 30
circle_x, circle_y = WIDTH // 2, HEIGHT // 2
circle_speed = 5
circle_color = (255, 0, 0)  # Vermelho

# Loop principal
running = True
while running:
    for event in pygame.event.get():
        if event.type == QUIT:
            running = False

    # Movimentação do círculo com as teclas
    keys = pygame.key.get_pressed()
    if keys[K_UP]:
        circle_y -= circle_speed
    if keys[K_DOWN]:
        circle_y += circle_speed
    if keys[K_LEFT]:
        circle_x -= circle_speed
    if keys[K_RIGHT]:
        circle_x += circle_speed

    # Limita o círculo dentro da tela
    circle_x = max(circle_radius, min(WIDTH - circle_radius, circle_x))
    circle_y = max(circle_radius, min(HEIGHT - circle_radius, circle_y))

    # Preenchimento da tela e desenho do círculo
    screen.fill((0, 0, 0))  # Cor de fundo: preto
    pygame.draw.circle(screen, circle_color, (circle_x, circle_y), circle_radius)

    # Atualização da tela
    pygame.display.flip()

# Encerra o pygame
pygame.quit()
