#include "cpu.h"
#include "generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char**argv) {

    srand(time(NULL));   // Inicializacao da semente para os numeros aleatorios.

    if (argc != 3) {
        printf("Numero de argumentos invalidos! Sao 3.\n");
        printf("Linha de execucao: ./exe TIPO_INSTRUCAO [TAMANHO_RAM|ARQUIVO_DE_INSTRUCOES]\n");
        printf("\tExemplo 1 de execucao: ./exe random 10\n");
        printf("\tExemplo 3 de execucao: ./exe file arquivo_de_instrucoes.txt\n");
        return 0;
    }

    int ramSize;
    Machine machine;
    Instruction *instructions;

    if (strcmp(argv[1], "random") == 0) {
        ramSize = atoi(argv[2]);
        instructions = generateRandomInstructions(ramSize);
    } else if (strcmp(argv[1], "file") == 0) {
        instructions = readInstructions(argv[2], &ramSize);
    } 
    else if(strcmp(argv[1], "multiply") == 0){
        ramSize = atoi(argv[2]);
        int n1 = 5;
        int n2 = 3;
        instructions = generateMultiplicationInstructions(n1, n2, 1, 1);
    }
    else if(strcmp(argv[1], "division") == 0){
        ramSize = atoi(argv[2]);
        instructions = generateDivisionInstructions(103, 5);
    }
    else if(strcmp(argv[1], "expoente") == 0){
        ramSize = atoi(argv[2]);
        instructions = generateExponentiationInstructions(2, 10);
    }
    else if(strcmp(argv[1], "factorial") == 0){
        ramSize = atoi(argv[2]);
        instructions = generateFactorialInstructions(4);
    }
    else if(strcmp(argv[1], "ap") == 0){
        ramSize = atoi(argv[2]);
        instructions = generateAritmeticProgressionInstructions(2, 47, 3);
    }
    else {
        printf("Opcao invalida.\n");
        return 0;
    }
    
    printf("Iniciando a maquina...\n");
    start(&machine, instructions, ramSize);
    printRAM(&machine);
    run(&machine);
    printRAM(&machine);
    stop(&machine);
    printf("Finalizando a maquina...\n");
    return 0;
}