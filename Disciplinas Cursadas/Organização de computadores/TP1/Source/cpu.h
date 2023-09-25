#ifndef CPU_H
#define CPU_H

typedef struct {
    int opcode;
    int info1;
    int info2;
    int info3;
} Instruction;

typedef struct {
    float *items;
    int size;
} Memory;

typedef struct {
    Instruction* instructions;
    Memory RAM;
} Machine;

void start(Machine*, Instruction*, int);
void stop(Machine*);
void run(Machine*);
void printRAM(Machine*);

#endif // !CPU_H