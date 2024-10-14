/*
    Aluno: Felipe Braz Marques
    Matrícula: 22.1.4030

    Exercício:

a) Implemente e faça o upload aqui de um programa em C, que receba como entrada um valor n e retorne como saída o valor que está posição n da sequência de Fibonacci. A ordem de complexidade desse algoritmo/programa deve ser $\Theta(log n)$.

b) Mostre que a ordem de complexidade desse algoritmo é $\Theta(log n)$. Coloque como comentário no fonte do programa a análise de complexidade realizada.

BCC241 - PROJETO E ANALISE DE ALGORITMOS - Turma 11
*/

#include <stdio.h>
#include <string.h>

int main() {
    int n; // Custo: O(1) - Declaração da variável
    printf("Digite a posicao desejada na sequencia de Fibonacci: \n"); // Custo: O(1) - Custo da função de printar na tela
    scanf("%d", &n); // Custo: O(1) - Custo da função de armazenar na memória

    long long fib[2][2] = {{1,1},{1,0}}, ret[2][2] = {{1,0},{0,1}}, tmp[2][2] = {{0,0},{0,0}}; // Custo: O(1) - Alocando e inicializando as matrizes
    int i, j, k; // Custo: O(1) - Declaração de variáveis

    while (n) { // Custo: O(log n) - o loop será executado até que n seja reduzido a zero, o que ocorre em O(log n) iterações.
        if (n & 1) { // Custo: O(1) - verificando se n é ímpar.
            memset(tmp, 0, sizeof tmp); // Custo: O(1) - definindo todos os elementos da matriz tmp como zero.
            for (i = 0; i < 2; i++) // Custo: O(1) - percorrendo a matriz 2x2 em uma dimensão.
                for (j = 0; j < 2; j++) // Custo: O(1) - percorrendo a matriz 2x2 em uma dimensão.
                    for (k = 0; k < 2; k++) // Custo: O(1) - percorrendo a matriz 2x2 em uma dimensão.
                        tmp[i][j] = (tmp[i][j] + ret[i][k] * fib[k][j]); // Custo: O(1) - realizando uma multiplicação e uma adição de inteiros.
            for (i = 0; i < 2; i++)
                for (j = 0; j < 2; j++)
                    ret[i][j] = tmp[i][j]; // Custo: O(1) - atribuindo valores da matriz tmp para a matriz ret.
        }
        memset(tmp, 0, sizeof tmp); // Custo: O(1) - definindo todos os elementos da matriz tmp como zero.
        for (i = 0; i < 2; i++) // Custo: O(1) - percorrendo a matriz 2x2 em uma dimensão.
            for (j = 0; j < 2; j++) // Custo: O(1) - percorrendo a matriz 2x2 em uma dimensão.
                for (k = 0; k < 2; k++) // Custo: O(1) - percorrendo a matriz 2x2 em uma dimensão.
                    tmp[i][j] = (tmp[i][j] + fib[i][k] * fib[k][j]); // Custo: O(1) - realizando uma multiplicação e uma adição de inteiros.
        for (i = 0; i < 2; i++)
            for (j = 0; j < 2; j++)
                fib[i][j] = tmp[i][j]; // Custo: O(1) - atribuindo valores da matriz tmp para a matriz fib.
        n /= 2; // Custo: O(1) - dividindo n por 2.
    }
    
    printf("O valor na posicao %d da sequencia de Fibonacci e: %lld\n", n, ret[0][1]); // Custo: O(1)
    return 0; // Custo: O(1)
}

/*
Rodei o programa 20 vezes e obtive os seguintes resultados:

    f(0) =    0
    f(1) =    1
    f(2) =    1
    f(3) =    2
    f(4) =    3
    f(5) =    5
    f(6) =    8
    f(7) =   13
    f(8) =   21
    f(9) =   34
    f(10)=   55
    f(11)=   89
    f(12)=  144
    f(13)=  233
    f(14)=  377
    f(15)=  610
    f(16)=  987
    f(17)= 1597
    f(18)= 2584
    f(19)= 4181
    f(20)= 6765

Coferindo com os valores esperados, todos batem!
*/