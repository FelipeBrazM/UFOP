import pygame
import sys
import math

pygame.init()

WIDTH, HEIGHT = 800, 600
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Sistema Solar Simples")

clock = pygame.time.Clock()

sun_pos = (WIDTH // 2, HEIGHT // 2)

earth_orbit_radius = 200   
moon_orbit_radius = 50    

earth_angle = 0
moon_angle = 0

earth_speed = 0.01
moon_speed = 0.05

# Loop principal do jogo
while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

    # Atualização dos ângulos para as órbitas
    earth_angle += earth_speed
    moon_angle += moon_speed

    # Cálculo da posição da Terra
    earth_x = sun_pos[0] + earth_orbit_radius * math.cos(earth_angle)
    earth_y = sun_pos[1] + earth_orbit_radius * math.sin(earth_angle)
    earth_pos = (int(earth_x), int(earth_y))

    # Cálculo da posição da Lua (em órbita ao redor da Terra)
    moon_x = earth_x + moon_orbit_radius * math.cos(moon_angle)
    moon_y = earth_y + moon_orbit_radius * math.sin(moon_angle)
    moon_pos = (int(moon_x), int(moon_y))

    # Preenche a tela com a cor preta (fundo do espaço)
    screen.fill((0, 0, 0))

    # Desenha o Sol (amarelo)
    pygame.draw.circle(screen, (255, 255, 0), sun_pos, 30)
    # Desenha a Terra (azul)
    pygame.draw.circle(screen, (0, 0, 255), earth_pos, 15)
    # Desenha a Lua (cinza claro)
    pygame.draw.circle(screen, (200, 200, 200), moon_pos, 5)

    # Atualiza a tela
    pygame.display.flip()
    clock.tick(60)
