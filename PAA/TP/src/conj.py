# Problema do conjunto independente deve ser resolvido por meio de redução com custo polinimial ao problema do Clique, já implementado usando branch and bound.

import time

from clique import leProblema, geraSolucao, branchAndBoundClique

def geraComplemento(problema):
    numVertices = problema[0][0]  # Número de vértices (primeira linha da matriz)
    
    # Inicializa a matriz de complemento
    complemento = [[0] * numVertices for _ in range(numVertices)]
    
    # Preenche a matriz de complemento
    for i in range(numVertices):
        for j in range(numVertices):
            if i != j:  # Não considerar a diagonal principal
                complemento[i][j] = 1 - problema[i + 1][j]
    
    # Adiciona o número de vértices como a primeira linha da matriz de complemento
    complemento.insert(0, [numVertices])
    
    return complemento

def print_grafo(matriz):
    num_vertices = matriz[0][0]  # Número de vértices (primeira linha da matriz)
    
    print(f"Número de vértices: {num_vertices}")
    
    for i in range(1, num_vertices + 1):
        linha = ' '.join(str(valor) for valor in matriz[i])
        print(linha)

def print_conjunto_independente_maximo(solucao):
    indices = [i + 1 for i in range(len(solucao)) if solucao[i] == 1]
    print("\nConjunto independente máximo:", end=" ")
    print("{", end="")
    print(", ".join(map(str, indices)), end="")
    print("}")

def ConjuntoIndependenteMaximo(caminho_entrada):
    inicio = time.time()
    problema = leProblema(caminho_entrada) 
    complemento = geraComplemento(problema)

    melhorSolucao = geraSolucao(complemento)
    solucaoInicial = [-1] * complemento[0][0]
    
    melhorSolucao = branchAndBoundClique(solucaoInicial, 0, complemento, melhorSolucao)
    fim = time.time()

    print_conjunto_independente_maximo(melhorSolucao)
    print(f"Tempo de execução: {fim-inicio:.6f} segundos")

if __name__ == "__main__":
    for i in range(3):
        print(f"Instância: {i+1}")
        ConjuntoIndependenteMaximo(f"entradas/Conjunto_inde/entrada{i+1}.txt")
        print("\n")
