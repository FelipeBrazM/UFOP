import time

def le_problema(arquivo_entrada: str):
    with open(arquivo_entrada, 'r') as arquivo:
        qtd_variaveis = int(arquivo.readline().strip())
        entrada = []
        
        for linha in arquivo:
            clausula = [int(coluna) for coluna in linha.strip().split()]
            entrada.append(clausula)

    return qtd_variaveis, entrada


def solucao_inicial(qtd_variaveis: int):
    return [None] * qtd_variaveis


def verificar_solucao(problema, solucao):
    # Verificando se e completa
    for variavel in solucao:
        if variavel is None:
            return False

    for clausula in problema:
        satisfeita = False
        for variavel, valor_atual in zip(clausula, solucao):
            if variavel == 1:
                satisfeita = satisfeita or valor_atual
            elif variavel == 0:
                satisfeita = satisfeita or not valor_atual

        # Se uma clausula nao foi satisfeita, nao e necessario seguir
        # as disjuncoes se tornarao falsas
        if not satisfeita:
            return False
    return True


# A clausula e computavel quando todos os literais apos o i sao valores diferentes de -1
# pois ate o i-esimo eles ja foram preenchidos
def clausula_computavel(i, clausula, qtd_variaveis):  
    for j in range(i, qtd_variaveis):
        if clausula[j-1] == -1:
            return False
    return True
    

def construir_candidatos(solucao, i, problema, dominio):
    # Nao e possivel fazer mais testes, pois solucao ja possui todos os valores preenchidos
    if i > len(solucao): return []
       
    candidatos = dominio.copy()
    s_temp = solucao.copy()
    qtd_variaveis = len(problema[0])

    # Testando cada valor do dominio
    for c in dominio:
        s_temp[i-1] = c

        # Verifica se todas as clausulas possiveis podem ser satisfeitas com o valor candidato atual
        for clausula in problema:
            satisfeita = False  

            # Verificamos se os itens após o i-esimo nao sao -1, porque, se forem, nao podemos verificar a satisfabilidade da clausula ainda
            if clausula_computavel(i, clausula, qtd_variaveis):
                for variavel_atual, literal in enumerate(clausula):
                    if literal == 1:
                        satisfeita = satisfeita or s_temp[variavel_atual]
                    elif literal == 0:
                        satisfeita = satisfeita or not s_temp[variavel_atual]
            else:
                continue

            # Se nao satisfez a clausula atual, nao podera satisfazer as proximas, entao o ramo deste candidato pode ser removido
            if not satisfeita:
                candidatos.remove(c)
                break
    return candidatos


def backtrack(solucao, i, problema):
    dominio = [False, True]

    if verificar_solucao(problema, solucao):
        return True
    else:
        i = i + 1
        candidatos = construir_candidatos(solucao, i, problema, dominio)
        for c in candidatos:
            solucao[i-1] = c
            finished = backtrack(solucao, i, problema)
            if finished:
                return True
            solucao[i-1] = None

    return False


def SAT(caminho_problema):
    inicio = time.time()
    qtd_variaveis, problema = le_problema(caminho_problema)
    solucao = solucao_inicial(qtd_variaveis)
    solucao_encontrada = backtrack(solucao, 0, problema)
    fim = time.time()

    if solucao_encontrada:
        print("Solução encontrada:", solucao)
    else:
        print("Solução não encontrada")
    
    tempo_execucao = fim - inicio
    print(f"Tempo de execução: {tempo_execucao:.6f} segundos")


if __name__ == "__main__":
    for i in range(15):
        print(f"Instância {i+1}")
        SAT(f"entradas/SAT/entrada{i+1}.txt")
        print("\n")
