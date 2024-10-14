def le_problema(arquivo_entrada: str):
    qtd_variaveis = None
    entrada = []

    with open(arquivo_entrada, 'r') as arquivo:
        linhas_do_arquivo = arquivo.readlines()
        
        qtd_variaveis = int(linhas_do_arquivo[0])
        
        for linha in linhas_do_arquivo[1:]:
            linha = linha.replace('\n', '')
            colunas = linha.split(' ')
            entrada.append([])
            for coluna in colunas:
                entrada[-1].append(int(coluna))

    return  qtd_variaveis, entrada

def is_a_solution(p, s):
    # Verificando se é completa
    for variavel in s:
        if variavel is None:
            return False

    for clausula in p:
        satisfeita = False
        # Toda clausula terá sempre três literais
        for variavel, valor_atual in zip(clausula, s):
            if variavel == 1:
                satisfeita = satisfeita or valor_atual
            elif variavel == 0:
                satisfeita = satisfeita or not valor_atual

        # Se uma clausula não foi satisfeita, não é necessário seguir
        # as disjunções se tornarão falsas
        if not satisfeita:
            return False
    return True

qtd_variaveis, p = le_problema("src/entradas/SAT/teste5.txt")

import itertools

def generate_boolean_combinations(N):
    return reversed(list(itertools.product([True, False], repeat=N)))

# Exemplo de uso:
N = qtd_variaveis
combinacoes = generate_boolean_combinations(N)
for combinacao in combinacoes:
    print(is_a_solution(p, combinacao))


