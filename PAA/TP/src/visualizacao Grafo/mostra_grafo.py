# Código para printar um Grafo a partir de uma matriz de adjacência

# pip install networkx matplotlib
# pip install --upgrade six

import networkx as nx
import matplotlib.pyplot as plt

def printGrafo(matrizAdjacencia):
    numVertices = matrizAdjacencia[0][0]
    
    # Criar um grafo usando a biblioteca NetworkX
    G = nx.Graph()

    # Adicionar os vértices ao grafo
    for i in range(numVertices):
        G.add_node(i + 1)  # Adiciona o vértice (começando do 1)

    # Adicionar as arestas (conexões) ao grafo com base na matriz de adjacência
    for i in range(1, numVertices + 1):
        for j in range(i + 1, numVertices + 1):
            if matrizAdjacencia[i][j - 1] == 1:  # Há uma aresta entre o vértice i e o vértice j
                G.add_edge(i, j)

    # Desenhar o grafo
    pos = nx.spring_layout(G)  # Posição dos nós (para melhor visualização)
    nx.draw(G, pos, with_labels=True, node_color='lightblue', font_weight='bold', node_size=500)
    plt.show()

# Exemplo de uso:
matrizAdjacencia = [
[10],
[0, 0, 1, 1, 1, 0, 0, 1, 1, 1],
[0, 0, 1, 1, 0, 1, 0, 1, 0, 1],
[1, 1, 0, 0, 1, 1, 0, 0, 0, 0],
[1, 1, 0, 0, 0, 0, 1, 0, 0, 1],
[1, 0, 1, 0, 0, 1, 1, 1, 1, 0],
[0, 1, 1, 0, 1, 0, 1, 1, 1, 1],
[0, 0, 0, 1, 1, 1, 0, 1, 1, 0],
[1, 1, 0, 0, 1, 1, 1, 0, 1, 0],
[1, 0, 0, 0, 1, 1, 1, 1, 0, 1],
[1, 1, 0, 1, 0, 1, 0, 0, 1, 0],
]

printGrafo(matrizAdjacencia)
