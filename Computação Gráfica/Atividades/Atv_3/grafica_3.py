import pygame
import math

# Configuração geral
WIDTH, HEIGHT = 800, 600
center = (WIDTH // 2, HEIGHT // 2)

def transformacao_2d_rotacao(screen):
    """Exemplo de Transformação Geométrica 2D: Rotação"""
    rect_points = [[100, 100], [200, 100], [200, 200], [100, 200]]
    center = (150, 150)
    angle = 0

    running = True
    clock = pygame.time.Clock()
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
        angle += 1
        radians = math.radians(angle)
        rotated_points = [
            [
                center[0] + (x - center[0]) * math.cos(radians) - (y - center[1]) * math.sin(radians),
                center[1] + (x - center[0]) * math.sin(radians) + (y - center[1]) * math.cos(radians),
            ]
            for x, y in rect_points
        ]
        screen.fill((0, 0, 0))
        pygame.draw.polygon(screen, (0, 128, 255), rotated_points)
        pygame.display.flip()
        clock.tick(60)

def transformacao_3d_escala(screen):
    """Exemplo de Transformação Geométrica 3D: Escala"""
    cube_points = [
        [-50, -50, -50], [50, -50, -50], [50, 50, -50], [-50, 50, -50],
        [-50, -50, 50], [50, -50, 50], [50, 50, 50], [-50, 50, 50],
    ]
    scale = 2

    def project_3d_to_2d(point):
        z = point[2] + 200
        factor = 300 / z
        x = int(point[0] * factor + center[0])
        y = int(point[1] * factor + center[1])
        return x, y

    running = True
    clock = pygame.time.Clock()
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
        scaled_points = [[p[0] * scale, p[1] * scale, p[2] * scale] for p in cube_points]
        projected_points = [project_3d_to_2d(p) for p in scaled_points]
        edges = [
            (0, 1), (1, 2), (2, 3), (3, 0),
            (4, 5), (5, 6), (6, 7), (7, 4),
            (0, 4), (1, 5), (2, 6), (3, 7)
        ]
        screen.fill((0, 0, 0))
        for edge in edges:
            pygame.draw.line(screen, (0, 128, 255), projected_points[edge[0]], projected_points[edge[1]])
        pygame.display.flip()
        clock.tick(60)

def composicao_2d(screen):
    """Composição de Transformação 2D: Rotação + Translação"""
    rect_points = [[100, 100], [200, 100], [200, 200], [100, 200]]
    center = (150, 150)
    angle = 0

    running = True
    clock = pygame.time.Clock()
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
        angle += 1
        radians = math.radians(angle)
        rotated_points = [
            [
                center[0] + (x - center[0]) * math.cos(radians) - (y - center[1]) * math.sin(radians),
                center[1] + (x - center[0]) * math.sin(radians) + (y - center[1]) * math.cos(radians),
            ]
            for x, y in rect_points
        ]
        translated_points = [[x + 100, y + 50] for x, y in rotated_points]
        screen.fill((0, 0, 0))
        pygame.draw.polygon(screen, (0, 255, 128), translated_points)
        pygame.display.flip()
        clock.tick(60)

def composicao_3d(screen):
    """Composição de Transformação 3D: Rotação + Escala"""
    cube_points = [
        [-50, -50, -50], [50, -50, -50], [50, 50, -50], [-50, 50, -50],
        [-50, -50, 50], [50, -50, 50], [50, 50, 50], [-50, 50, 50],
    ]
    scale = 1.5
    angle = 0

    def project_3d_to_2d(point):
        z = point[2] + 200
        factor = 300 / z
        x = int(point[0] * factor + center[0])
        y = int(point[1] * factor + center[1])
        return x, y

    running = True
    clock = pygame.time.Clock()
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
        angle += 1
        rotated_points = [
            [
                p[0] * math.cos(math.radians(angle)) - p[2] * math.sin(math.radians(angle)),
                p[1],
                p[0] * math.sin(math.radians(angle)) + p[2] * math.cos(math.radians(angle)),
            ]
            for p in cube_points
        ]
        scaled_points = [[p[0] * scale, p[1] * scale, p[2] * scale] for p in rotated_points]
        projected_points = [project_3d_to_2d(p) for p in scaled_points]
        edges = [
            (0, 1), (1, 2), (2, 3), (3, 0),
            (4, 5), (5, 6), (6, 7), (7, 4),
            (0, 4), (1, 5), (2, 6), (3, 7)
        ]
        screen.fill((0, 0, 0))
        for edge in edges:
            pygame.draw.line(screen, (255, 128, 0), projected_points[edge[0]], projected_points[edge[1]])
        pygame.display.flip()
        clock.tick(60)

def main():
    pygame.init()
    screen = pygame.display.set_mode((WIDTH, HEIGHT))
    pygame.display.set_caption("Transformações Geométricas com Pygame")

    while True:
        print("Escolha uma transformação para visualizar:")
        print("1 - Transformação 2D: Rotação")
        print("2 - Transformação 3D: Escala")
        print("3 - Composição 2D: Rotação + Translação")
        print("4 - Composição 3D: Rotação + Escala")
        print("5 - Sair")

        choice = input("Digite o número da transformação desejada: ")

        if choice == "1":
            transformacao_2d_rotacao(screen)
        elif choice == "2":
            transformacao_3d_escala(screen)
        elif choice == "3":
            composicao_2d(screen)
        elif choice == "4":
            composicao_3d(screen)
        elif choice == "5":
            print("Encerrando o programa.")
            break
        else:
            print("Opção inválida. Tente novamente.")

    pygame.quit()

if __name__ == "__main__":
    main()
