#ifndef CPU_H
#define CPU_H

#include "instruction.h"
#include "memory.h"

typedef struct {
    Instruction* instructions;
    RAM ram;
    Cache l1; // cache L1
    Cache l2; // cache L2
    Cache l3; // cache l3
    int hitL1, hitL2, hitL3, hitRAM;
    int missL1, missL2, missL3;
    int totalCost;
} Machine;


#if defined LFU || defined LRU || defined FIFO
    void inicializaContador(Cache * cache);
#endif

void start(Machine*, Instruction*, int*);
void stop(Machine*);
void run(Machine*);
void printMemories(Machine*);

#endif // !CPU_H