# Problema de Clique usando Branch and Bound
# Clique – Dado um grafo, encontre um conjunto maximo de vertices tal que todas as possiveis arestas entre eles estejam presentes.
import time

def leProblema(caminho_entrada):
    entrada = []

    with open(caminho_entrada, 'r') as arquivo:
        for linha in arquivo:
            colunas = linha.split(' ')
            
            for i, _ in enumerate(colunas):
                colunas[i] = int(colunas[i])

            entrada.append(colunas)
    
    return entrada

def geraSolucao(problema):
    """Busca na matriz de adjancencia uma conexao entre dois vertices, gerando uma solucao que possui 2 vertices
       Caso nao encontre nenhuma conexao, gera uma solucao com apenas 1 vertice"""
    solucao = [0] * problema[0][0]

    for i in range(problema[0][0]):
        for j in range(problema[0][0]):
            if(problema[i+1][j] == 1):
                solucao[i] = 1
                solucao[j] = 1
                return solucao

    solucao[0] = 1
    return solucao

def eCompleta(solucao):
    """Verifica se nenhuma posicao do vetor solucao tem valor -1, ou seja, todas as posicoes ja teriam valores 0 ou 1 atribuidos"""
    return not -1 in solucao

def eConsistente(solucao, problema, i):
    """Verifica se todos os vertices da solucao ate o momento estao totalmente conectados entre si"""
    verticesNaSolucao = [] # armazena os vertices que estao presentes na solucao construida ate o momento
    
    for j in range(i+1):
        if solucao[j] == 1:
            verticesNaSolucao.append(j)

    # faz a verificacao se existe arestas entre todos os vertices presentes na solucao
    for j in range(len(verticesNaSolucao)-1):
        for k in range(j+1, len(verticesNaSolucao)):
            # como a variavel 'problema' armazena na primeira linha o numero de vertices do grafo, e necessario somar 1 para acessar a linha correta da matriz de adjacencia
            if(problema[verticesNaSolucao[j]+1][verticesNaSolucao[k]] == 0): 
                return False
            
    return True 
            
def ePromissora(solucao, problema, melhor, i):
    """Verifica se o numero maximo de vertices que a solucao pode vir a ter e maior que o numero de vertices da melhor solucao ate entao"""
    numVerticesMelhor = sum(melhor) # como a solucao possui apenas 0s e 1s, se eu somar os valores de suas posicoes, saberei quantos vertices fazem parte da solucao
    numVerticesMaximoSolucao = 0 # armazena o numero maximo de vertices possiveis na solucao construida ate entao
    
    # soma os valores das posicoes ate a variavel da solucao que ja teve valor atribuido ate o momento
    for j in range(i+1):
        numVerticesMaximoSolucao += solucao[j]

    # com as demais variaveis sem valores atribuidos, no maximo todas receberiam valor 1, e, portanto,
    # para termos o numero maximo de vertices basta somar o numero de variaveis sem valores atribuidos
    numVerticesMaximoSolucao += (problema[0][0] - (i+1))
    
    return numVerticesMaximoSolucao > numVerticesMelhor

def branchAndBoundClique(solucao, i, problema, melhor):
    if eCompleta(solucao):
        melhor[:] = solucao
        return melhor
    
    else:
        for j in range(2): # o dominio das variaveis da solucao e [0, 1]
            solucao[i] = j
            
            if(eConsistente(solucao, problema, i) and ePromissora(solucao, problema, melhor, i)):
                melhor = branchAndBoundClique(solucao, i+1, problema, melhor)
            
            solucao[i] = -1
        
        return melhor

def Clique(caminho_entrada):
    """A solucao sera um vetor com o numero de posicoes igual ao numero de vertices do grafo
       As posicoes do vetor possuirao o valor 1 caso o vertice pertenca a solucao, e 0 caso contrario"""
    inicio = time.time()

    problema = leProblema(caminho_entrada) # armazena na primeira linha o numero de vertices do grafo, e nas demais linhas a matriz de adjacencia
    melhorSolucao = geraSolucao(problema)
    solucaoInicial = [-1] * problema[0][0] # vetor com tamanho do numero de vertices e com valores -1 para representar que nao tem nenhum valor atribuido as variaveis
    
    melhorSolucao = branchAndBoundClique(solucaoInicial, 0, problema, melhorSolucao)

    fim = time.time()

    print(melhorSolucao)

    print("Vértices presentes no clique:")
    for i in range(len(melhorSolucao)):
        if(melhorSolucao[i] == 1):
            print(i+1)

    print(f"Tempo de execução: {fim-inicio:.6f} segundos")

if __name__ == "__main__":
    for i in range(3):
        print(f"Instância: {i+1}")
        Clique(f"entradas/Clique/entradaClique{i+1}.txt")
        print("\n")