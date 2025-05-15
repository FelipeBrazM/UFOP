import pygame

# Inicializar o pygame
pygame.init()

# Configuração da tela
screen_width, screen_height = 800, 600
screen = pygame.display.set_mode((screen_width, screen_height))
pygame.display.set_caption("Movimentação do Quadrado")

# Definições do quadrado
square_size = 50
square_color = (255, 0, 0)  # Vermelho
square_x = screen_width // 2 - square_size // 2
square_y = screen_height // 2 - square_size // 2
speed = 5  # Velocidade de movimento

# Loop principal
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Capturar teclas pressionadas
    keys = pygame.key.get_pressed()
    if keys[pygame.K_DOWN]:  # Seta para baixo
        square_y += speed
    if keys[pygame.K_UP]:  # Seta para cima
        square_y -= speed
    if keys[pygame.K_LEFT]:  # Seta para a esquerda
        square_x -= speed
    if keys[pygame.K_RIGHT]:  # Seta para a direita
        square_x += speed

    # Garantir que o quadrado permaneça visível na tela
    square_x = max(0, min(screen_width - square_size, square_x))
    square_y = max(0, min(screen_height - square_size, square_y))

    # Atualizar a tela
    screen.fill((0, 0, 0))  # Fundo preto
    pygame.draw.rect(screen, square_color, (square_x, square_y, square_size, square_size))
    pygame.display.flip()

# Encerrar o pygame
pygame.quit()
