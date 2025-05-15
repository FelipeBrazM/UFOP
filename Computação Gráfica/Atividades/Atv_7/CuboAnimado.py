import pygame
from pygame.locals import *
from OpenGL.GL import *
from OpenGL.GLU import *
import math

# Inicialização
pygame.init()
width, height = 800, 600
pygame.display.set_mode((width, height), DOUBLEBUF | OPENGL)

# Configurações iniciais
glEnable(GL_DEPTH_TEST)
glClearColor(0.0, 0.0, 0.0, 1.0)

# Variáveis de controle
scale = 1.0
growing = True
projection_mode = 'perspective'  # 'perspective' ou 'ortho'

# Configuração inicial da projeção
def set_projection():
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    aspect_ratio = width / height
    
    if projection_mode == 'perspective':
        gluPerspective(45, aspect_ratio, 0.1, 50.0)
    else:  # ortho
        ortho_size = 5
        glOrtho(-ortho_size * aspect_ratio, ortho_size * aspect_ratio, 
                -ortho_size, ortho_size, -50, 50)
    
    glMatrixMode(GL_MODELVIEW)

set_projection()

# Função para desenhar o cubo
def draw_cube():
    glBegin(GL_LINES)
    
    # Frente
    glVertex3f(-1, -1, 1)
    glVertex3f(1, -1, 1)
    
    glVertex3f(1, -1, 1)
    glVertex3f(1, 1, 1)
    
    glVertex3f(1, 1, 1)
    glVertex3f(-1, 1, 1)
    
    glVertex3f(-1, 1, 1)
    glVertex3f(-1, -1, 1)
    
    # Trás
    glVertex3f(-1, -1, -1)
    glVertex3f(1, -1, -1)
    
    glVertex3f(1, -1, -1)
    glVertex3f(1, 1, -1)
    
    glVertex3f(1, 1, -1)
    glVertex3f(-1, 1, -1)
    
    glVertex3f(-1, 1, -1)
    glVertex3f(-1, -1, -1)
    
    # Conexões
    glVertex3f(-1, -1, 1)
    glVertex3f(-1, -1, -1)
    
    glVertex3f(1, -1, 1)
    glVertex3f(1, -1, -1)
    
    glVertex3f(1, 1, 1)
    glVertex3f(1, 1, -1)
    
    glVertex3f(-1, 1, 1)
    glVertex3f(-1, 1, -1)
    
    glEnd()

# Loop principal
clock = pygame.time.Clock()
running = True

while running:
    # Eventos
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_p:
                projection_mode = 'perspective'
                set_projection()
            elif event.key == pygame.K_o:
                projection_mode = 'ortho'
                set_projection()
    
    # Lógica da animação
    if growing:
        scale += 0.01
        if scale >= 2.0:
            growing = False
    else:
        scale -= 0.01
        if scale <= 0.5:
            growing = True
    
    # Renderização
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()
    
    # Posiciona a câmera
    gluLookAt(3, 3, 3, 0, 0, 0, 0, 1, 0)
    
    # Aplica a escala e desenha o cubo
    glScalef(scale, scale, scale)
    draw_cube()
    
    pygame.display.flip()
    clock.tick(60)

pygame.quit()