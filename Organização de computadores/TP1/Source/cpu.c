#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>

void start(Machine* machine, Instruction* instructions, int RAMSize) {
    machine->instructions = instructions;
    machine->RAM.items = (float*) malloc(sizeof(float) * RAMSize);
    machine->RAM.size = RAMSize;
    for (int i=0;i<RAMSize;i++)
        machine->RAM.items[i] = (float)rand() / RAND_MAX;
}

void stop(Machine* machine) {
    free(machine->instructions);
    free(machine->RAM.items);
}

void run(Machine* machine) {
    // Registradores
    int PC = 0; // Program Counter - Contador de programa
    int opcode = 0;
    int address1;
    int address2;
    float value;
    float result;
    float RAMContent1;
    float RAMContent2;
    int address3;
    while(opcode != -1) {
        Instruction instruction = machine->instructions[PC];
        opcode = instruction.opcode;
        switch (opcode) {
            case -1:
                printf("  > Finalizando a execucao.\n");
                break;
            case 0: // Levando informação para a RAM
                value = (float) instruction.info1;
                address1 = instruction.info2;
                machine->RAM.items[address1] = value;
                printf("  > Levando informacao (%f) para a RAM[%d].\n", value, address1);
                break;
            case 1: // Somando
                address1 = instruction.info1;
                address2 = instruction.info2;
                RAMContent1 = machine->RAM.items[address1];
                RAMContent2 = machine->RAM.items[address2];
                result = RAMContent1 + RAMContent2;
                address3 = instruction.info3;
                machine->RAM.items[address3] = result;
                printf("  > Somando RAM[%d] (%f) com RAM[%d] (%f) e salvando na RAM[%d] (%f).\n", 
                                address1, RAMContent1, address2, RAMContent2, address3, result);
                break;
            case 2: // Subtraindo
                address1 = instruction.info1;
                address2 = instruction.info2;
                RAMContent1 = machine->RAM.items[address1];
                RAMContent2 = machine->RAM.items[address2];
                result = RAMContent1 - RAMContent2;
                address3 = instruction.info3;
                machine->RAM.items[address3] = result;
                printf("  > Subtraindo RAM[%d] (%f) com RAM[%d] (%f) e salvando na RAM[%d] (%f).\n", 
                                address1, RAMContent1, address2, RAMContent2, address3, result);
                break;
        }
        PC++;
    }
}

void printRAM(Machine* machine) {
    printf("  > RAM");
    for (int i=0;i<machine->RAM.size;i++)
        printf("\t\t[%5d] : %f\n", i, machine->RAM.items[i]);
}
