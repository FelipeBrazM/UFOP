//Gerador de instruções feito por Luísa Calegari, Thiago Cecote e Josué Vila Real
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N_INST 10000 //numero de instrucoes
#define N_FOR 5     //numero de instrucoes que vao se repetir
#define N_MEM 1000  //numero da memoria para endereco do bloco
#define N_PROB 50   //probabilidade de repeticao
#define N_OPCODE 3  //numero maximo de opcodes
#define N_WORD 4    //numero de palavras no bloco

void instGenerator(char*);

/*int main(int argc, char**argv) {
    if (argc != 2) {
        printf("Numero de argumentos invalidos! Sao 2.\n");
        printf("Linha de execucao: ./exe \"path/nome arquivo.in\"\n");
        printf("\tExemplo de execucao: ./exe instrucao.in\n");
        return 0;
    }
    instGenerator(argv[1]);
    return 0;
}*/

void instGenerator(char* fileName) {
    int rep[5][7];
    int inst[10000][7];
    FILE *arquivo = fopen(fileName, "w");
    int random;
    int instruc[8] = {6, 6, 6, 6, 6, 6, 6, 6};
    srand(time(NULL));

    for (int i = 0; i < N_FOR; i++) {
        random = rand() % N_OPCODE;
        rep[i][0] = random;
        for (int j = 1; j <= (instruc[random]); j += 2) {
            rep[i][j] = rand() % N_MEM;
            rep[i][j + 1] = rand() % N_WORD;
        }
    }

    for (int i = 0; i < N_INST;) {
        random = (rand() % 100) + 1;
        if (random <= N_PROB && i + N_FOR < N_INST) {
            for (int j = 0; j < N_FOR; j++) {
                for (int k = 0; k < 7; k++) {
                    inst[i + j][k] = rep[j][k];
                }
            }
            i += N_FOR;
        } else {
            random = rand() % N_OPCODE;
            inst[i][0] = random;
            for (int j = 1; j <= instruc[random]; j += 2) {
                inst[i][j] = rand() % N_MEM;
                inst[i][j + 1] = rand() % N_WORD;
            }
            i++;
        }
    }
    fprintf(arquivo, "%d %d\n", N_INST, N_MEM);
    
    for (int i = 0; i < N_INST - 1; i++) {
        for (int k = 0; k < 6; k++) {
            fprintf(arquivo, "%d ", inst[i][k]);
        }
        fprintf(arquivo, "%d\n", inst[i][6]);
    }

    fprintf(arquivo, "-1 -1 -1 -1 -1 -1 -1");

    fclose(arquivo);
}
