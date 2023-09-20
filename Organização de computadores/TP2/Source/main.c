#include "cpu.h"
#include "generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char**argv) {

    srand(1507);   // Inicializacao da semente para os numeros aleatorios.

    if (argc != 6) {
        printf("Numero de argumentos invalidos! Sao 6.\n");
        printf("Linha de execucao: ./exe TIPO_INSTRUCAO [TAMANHO_RAM|ARQUIVO_DE_INSTRUCOES] TAMANHO_L1 TAMANHO_L2 TAMANHO_L3\n");
        printf("\tExemplo 1 de execucao: ./exe random 10 2 4 5\n");
        printf("\tExemplo 2 de execucao: ./exe file arquivo_de_instrucoes.txt\n");
        return 0;
    }
    /*else if(!( 
        atoi(argv[5]) > atoi(argv[4]) &&
        atoi(argv[4]) > atoi(argv[3]) &&
        atoi(argv[2]) > atoi(argv[5])
       )){
        printf("\033[91mValores incorretos para o tamanho das memorias!\n\033[0m");
        printf("\tValores correros: RAM > Cache L3 > Cache L2 > Cache L1\n");
        printf("\033[93mOs valores são passados por: ./exe TIPO_INSTRUCAO TAMANHO_DA_RAM TAMANHO_L1 TAMANHO_L2 TAMANHO_L3\n\033[0m");
        return 0;
    }*/

    int memoriesSize[4];
    Machine machine;
    Instruction *instructions;

    memoriesSize[1] = atoi(argv[3]);
    memoriesSize[2] = atoi(argv[4]);
    memoriesSize[3] = atoi(argv[5]);

    if (strcmp(argv[1], "random") == 0) {
        memoriesSize[0] = atoi(argv[2]);
        instructions = generateRandomInstructions(memoriesSize[0]);
    } else if (strcmp(argv[1], "file") == 0) {
        instructions = readInstructions(argv[2], memoriesSize);
    } 
    else {
        printf("Invalid option.\n");
        return 0;
    }
    
    printf("Starting machine...\n");
    start(&machine, instructions, memoriesSize);
    if (memoriesSize[0] <= 100)
        printMemories(&machine);
    run(&machine);
    if (memoriesSize[0] <= 100)
        printMemories(&machine);
    stop(&machine);
    printf("Stopping machine...\n");
    return 0;
}