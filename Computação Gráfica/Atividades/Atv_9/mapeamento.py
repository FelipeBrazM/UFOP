import sys, pygame
from pygame.locals import *
from OpenGL.GL import *
from OpenGL.GLU import *

def load_texture(image_path):
    # Carrega a imagem com o pygame e cria a textura no OpenGL
    textureSurface = pygame.image.load(image_path)
    textureData = pygame.image.tostring(textureSurface, "RGBA", 1)
    width = textureSurface.get_width()
    height = textureSurface.get_height()
    texID = glGenTextures(1)
    glBindTexture(GL_TEXTURE_2D, texID)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, textureData)
    return texID

def draw_cube(tex_offset_x, tex_offset_y, tex_scale):
    # Desenha um cubo com coordenadas de textura modificadas
    glBegin(GL_QUADS)
    # Face frontal
    glTexCoord2f(0 * tex_scale + tex_offset_x, 0 * tex_scale + tex_offset_y)
    glVertex3f(-1, -1,  1)
    glTexCoord2f(1 * tex_scale + tex_offset_x, 0 * tex_scale + tex_offset_y)
    glVertex3f( 1, -1,  1)
    glTexCoord2f(1 * tex_scale + tex_offset_x, 1 * tex_scale + tex_offset_y)
    glVertex3f( 1,  1,  1)
    glTexCoord2f(0 * tex_scale + tex_offset_x, 1 * tex_scale + tex_offset_y)
    glVertex3f(-1,  1,  1)
    
    # Face traseira
    glTexCoord2f(1 * tex_scale + tex_offset_x, 0 * tex_scale + tex_offset_y)
    glVertex3f(-1, -1, -1)
    glTexCoord2f(1 * tex_scale + tex_offset_x, 1 * tex_scale + tex_offset_y)
    glVertex3f(-1,  1, -1)
    glTexCoord2f(0 * tex_scale + tex_offset_x, 1 * tex_scale + tex_offset_y)
    glVertex3f( 1,  1, -1)
    glTexCoord2f(0 * tex_scale + tex_offset_x, 0 * tex_scale + tex_offset_y)
    glVertex3f( 1, -1, -1)
    
    # Face esquerda
    glTexCoord2f(0 * tex_scale + tex_offset_x, 0 * tex_scale + tex_offset_y)
    glVertex3f(-1, -1, -1)
    glTexCoord2f(1 * tex_scale + tex_offset_x, 0 * tex_scale + tex_offset_y)
    glVertex3f(-1, -1,  1)
    glTexCoord2f(1 * tex_scale + tex_offset_x, 1 * tex_scale + tex_offset_y)
    glVertex3f(-1,  1,  1)
    glTexCoord2f(0 * tex_scale + tex_offset_x, 1 * tex_scale + tex_offset_y)
    glVertex3f(-1,  1, -1)
    
    # Face direita
    glTexCoord2f(1 * tex_scale + tex_offset_x, 0 * tex_scale + tex_offset_y)
    glVertex3f( 1, -1, -1)
    glTexCoord2f(1 * tex_scale + tex_offset_x, 1 * tex_scale + tex_offset_y)
    glVertex3f( 1,  1, -1)
    glTexCoord2f(0 * tex_scale + tex_offset_x, 1 * tex_scale + tex_offset_y)
    glVertex3f( 1,  1,  1)
    glTexCoord2f(0 * tex_scale + tex_offset_x, 0 * tex_scale + tex_offset_y)
    glVertex3f( 1, -1,  1)
    
    # Face superior
    glTexCoord2f(0 * tex_scale + tex_offset_x, 1 * tex_scale + tex_offset_y)
    glVertex3f(-1,  1, -1)
    glTexCoord2f(0 * tex_scale + tex_offset_x, 0 * tex_scale + tex_offset_y)
    glVertex3f(-1,  1,  1)
    glTexCoord2f(1 * tex_scale + tex_offset_x, 0 * tex_scale + tex_offset_y)
    glVertex3f( 1,  1,  1)
    glTexCoord2f(1 * tex_scale + tex_offset_x, 1 * tex_scale + tex_offset_y)
    glVertex3f( 1,  1, -1)
    
    # Face inferior
    glTexCoord2f(1 * tex_scale + tex_offset_x, 1 * tex_scale + tex_offset_y)
    glVertex3f(-1, -1, -1)
    glTexCoord2f(0 * tex_scale + tex_offset_x, 1 * tex_scale + tex_offset_y)
    glVertex3f( 1, -1, -1)
    glTexCoord2f(0 * tex_scale + tex_offset_x, 0 * tex_scale + tex_offset_y)
    glVertex3f( 1, -1,  1)
    glTexCoord2f(1 * tex_scale + tex_offset_x, 0 * tex_scale + tex_offset_y)
    glVertex3f(-1, -1,  1)
    glEnd()

def main():
    pygame.init()
    display = (800, 600)
    pygame.display.set_mode(display, DOUBLEBUF | OPENGL)
    gluPerspective(45, display[0] / display[1], 0.1, 50.0)
    glTranslatef(0.0, 0.0, -5)
    
    # Habilita o mapeamento de textura
    glEnable(GL_TEXTURE_2D)
    texture_id = load_texture("texture.png")  # Coloque um arquivo "texture.png" no mesmo diretório

    # Parâmetros iniciais de mapeamento
    tex_offset_x = 0.0
    tex_offset_y = 0.0
    tex_scale = 1.0

    clock = pygame.time.Clock()
    running = True
    while running:
        for event in pygame.event.get():
            if event.type == QUIT:
                running = False
            elif event.type == KEYDOWN:
                if event.key == K_ESCAPE:
                    running = False
                # Ajusta o offset da textura com as setas
                elif event.key == K_LEFT:
                    tex_offset_x -= 0.1
                elif event.key == K_RIGHT:
                    tex_offset_x += 0.1
                elif event.key == K_UP:
                    tex_offset_y += 0.1
                elif event.key == K_DOWN:
                    tex_offset_y -= 0.1
                # Ajusta a escala da textura com A e S
                elif event.key == K_a:
                    tex_scale = max(0.1, tex_scale - 0.1)
                elif event.key == K_s:
                    tex_scale += 0.1
                # Reseta os parâmetros
                elif event.key == K_r:
                    tex_offset_x = 0.0
                    tex_offset_y = 0.0
                    tex_scale = 1.0

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glLoadIdentity()
        gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0)
        glBindTexture(GL_TEXTURE_2D, texture_id)
        draw_cube(tex_offset_x, tex_offset_y, tex_scale)
        pygame.display.flip()
        clock.tick(60)
    pygame.quit()
    sys.exit()

if __name__ == "__main__":
    main()
