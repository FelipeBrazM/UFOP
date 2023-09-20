#include "generator.h"
#include <stdio.h>
#include <stdlib.h>

Instruction* generateRandomInstructions(int ramSize) {
    // 01|22|13|45 => this is an instruction
    // 02|33|12|01 => this is another instruction
            
    // 0 => opcode => move
    // 1 => opcode => sum
    // 2 => opcode => subtract
    //-1 => halt
    
    int n = 100;

    Instruction* instructions = (Instruction*) malloc((n + 1) * sizeof(Instruction));

    for (int i=0; i<n; i++) {
        instructions[i].add1.block = rand() % ramSize;
        instructions[i].add1.word = rand() % WORDS_SIZE;
        instructions[i].add2.block = rand() % ramSize;
        instructions[i].add2.word = rand() % WORDS_SIZE;
        instructions[i].add3.block = rand() % ramSize;
        instructions[i].add3.word = rand() % WORDS_SIZE;
        instructions[i].opcode = rand() % 3;
    }
    instructions[n].opcode = -1;
    
    return instructions;
}

Instruction* readInstructions(char* fileName, int* memoriesSize) {
    Instruction* instructions = NULL;

    printf("FILE -> %s\n", fileName);
    FILE* file = fopen(fileName, "r"); // Open file in read mode
    
    if (file == NULL) {
        printf("Arquivo nao pode ser aberto.\n");
        exit(1);
    }

    int n, i = 0;
    fscanf(file, "%d %d", &n, &memoriesSize[0]);
    instructions = (Instruction*) malloc(n * sizeof(Instruction));
    while (i < n) {
        fscanf(file, "%d %d %d %d %d %d %d", 
            &instructions[i].opcode, 
            &instructions[i].add1.block, &instructions[i].add1.word,
            &instructions[i].add2.block, &instructions[i].add2.word,
            &instructions[i].add3.block, &instructions[i].add3.word);
        i++;
    }
    fclose(file); // Close file

    return instructions;
}
