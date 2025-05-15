import sys, math, pygame
from pygame.locals import *
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import glutInit, glutSolidCube, glutSolidSphere

# Inicialização do Pygame, OpenGL e GLUT
pygame.init()
display = (800, 600)
pygame.display.set_mode(display, DOUBLEBUF | OPENGL)
glutInit()

# Habilita o teste de profundidade e a iluminação
glEnable(GL_DEPTH_TEST)
glEnable(GL_LIGHTING)
glEnable(GL_LIGHT0)
glShadeModel(GL_SMOOTH)

# Define as propriedades do material do cubo
glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, [0.8, 0.3, 0.3, 1.0])
glMaterialfv(GL_FRONT, GL_SPECULAR, [1.0, 1.0, 1.0, 1.0])
glMaterialf(GL_FRONT, GL_SHININESS, 50)

# Define as propriedades da luz (ambient, difusa e especular)
glLightfv(GL_LIGHT0, GL_AMBIENT, [0.2, 0.2, 0.2, 1.0])
glLightfv(GL_LIGHT0, GL_DIFFUSE, [0.8, 0.8, 0.8, 1.0])
glLightfv(GL_LIGHT0, GL_SPECULAR, [1.0, 1.0, 1.0, 1.0])

# Configura a projeção
glMatrixMode(GL_PROJECTION)
glLoadIdentity()
gluPerspective(45, (display[0] / display[1]), 0.1, 50.0)
glMatrixMode(GL_MODELVIEW)

# Parâmetros iniciais da luz
# light_mode: "directional", "point" ou "spotlight"
light_mode = "directional"
light_x, light_y, light_z = 0.0, 5.0, 5.0
spot_cutoff = 30.0  # Ângulo de corte para spotlight

# Função para calcular a direção do spotlight (do ponto da luz para a origem)
def update_spot_direction():
    dx = -light_x
    dy = -light_y
    dz = -light_z
    length = math.sqrt(dx * dx + dy * dy + dz * dz)
    if length == 0:
        return [0.0, -1.0, -1.0]
    return [dx / length, dy / length, dz / length]

# Atualiza as propriedades da luz conforme o modo selecionado
def update_light():
    if light_mode == "directional":
        # Luz direcional: w = 0
        light_pos = [light_x, light_y, light_z, 0.0]
        glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, [180.0])
    elif light_mode == "point":
        # Luz pontual: w = 1, sem efeito de spotlight (cutoff 180)
        light_pos = [light_x, light_y, light_z, 1.0]
        glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, [180.0])
    elif light_mode == "spotlight":
        # Spotlight: w = 1 e ângulo de corte definido
        light_pos = [light_x, light_y, light_z, 1.0]
        glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, [spot_cutoff])
        spot_dir = update_spot_direction()
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_dir)
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos)

clock = pygame.time.Clock()
running = True

while running:
    # Processa eventos
    for event in pygame.event.get():
        if event.type == QUIT:
            running = False
        elif event.type == KEYDOWN:
            if event.key == K_ESCAPE:
                running = False
            # Alterna entre os modos de luz: 1 - Direcional, 2 - Pontual, 3 - Spotlight
            elif event.key == K_1:
                light_mode = "directional"
            elif event.key == K_2:
                light_mode = "point"
            elif event.key == K_3:
                light_mode = "spotlight"
            # Ajusta o ângulo do spotlight com [ e ]
            elif event.key == K_LEFTBRACKET:
                if spot_cutoff > 5:
                    spot_cutoff -= 5
            elif event.key == K_RIGHTBRACKET:
                if spot_cutoff < 90:
                    spot_cutoff += 5

    # Ajusta a posição da luz com as setas e PgUp/PgDown
    keys = pygame.key.get_pressed()
    if keys[K_LEFT]:
        light_x -= 0.1
    if keys[K_RIGHT]:
        light_x += 0.1
    if keys[K_UP]:
        light_z -= 0.1
    if keys[K_DOWN]:
        light_z += 0.1
    if keys[K_PAGEUP]:
        light_y += 0.1
    if keys[K_PAGEDOWN]:
        light_y -= 0.1

    # Atualiza a luz
    update_light()

    # Limpa os buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()
    # Define a câmera
    gluLookAt(0, 3, 15,   # posição do olho
              0, 0, 0,    # para onde a câmera olha (origem)
              0, 1, 0)    # vetor up

    # Desenha o cubo (rotaciona ao longo do tempo para melhor visualização dos efeitos)
    glPushMatrix()
    glRotatef(pygame.time.get_ticks() / 50.0, 1, 1, 0)
    glutSolidCube(3)
    glPopMatrix()

    # Desenha uma pequena esfera amarela na posição da luz para visualizá-la
    glPushMatrix()
    glDisable(GL_LIGHTING)  # desabilita a iluminação para desenhar o marcador de luz
    glColor3f(1, 1, 0)
    glTranslatef(light_x, light_y, light_z)
    glutSolidSphere(0.2, 16, 16)
    glEnable(GL_LIGHTING)
    glPopMatrix()

    pygame.display.flip()
    clock.tick(60)

pygame.quit()
sys.exit()
