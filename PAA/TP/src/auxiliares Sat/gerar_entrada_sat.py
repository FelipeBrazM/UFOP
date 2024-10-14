import random
import itertools


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
                candidatos.pop(0)
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

def SAT(problema, n):
    solucao = solucao_inicial(n)
    solucao_encontrada = backtrack(solucao, 0, problema)
    return solucao_encontrada



n = random.randint(15, 20)
clausulas = 4096

print(n, clausulas)

while True:
    problema = []
    for i in range(clausulas):
        literais = []
        for j in range(n):
            literal = random.randint(-1, 1)
            literais.append(literal)
        problema.append(literais) 

    if SAT(problema, n):
        for linha in problema:
            linha = [ str(l) for l in linha]
            print(" ".join(linha))
        break

