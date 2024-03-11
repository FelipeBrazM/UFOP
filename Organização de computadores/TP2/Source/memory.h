#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>
#include <stdbool.h>

#include "constants.h"

typedef struct {
    int words[WORDS_SIZE];
} MemoryBlock;

typedef struct {
    MemoryBlock* blocks;
    int size;
} RAM;

typedef struct {
    MemoryBlock block;
    int tag; /* Address of the block in memory RAM */
    bool updated;
    int cost;
    int cacheHit;
    
    #if defined LFU || defined LRU || defined FIFO
        // LFU -> Quantas vezes ele foi utilizado - Procura o menor valor - incrementa +1 onde deu cache hit
        // LRU -> ha quanto tempo ele nao foi usado - Procura o maior valor - Volta para zero sempre que for usado
        // FIFO -> Qual o maior valor para sair, indicando estar a mais tempo
        int contador;
    #endif

} Line;

#ifdef LRU


#endif

typedef struct {
    Line* lines;
    int size;

} Cache;

void startCache(Cache*, int);
void stopCache(Cache*);

void startRAM(RAM*, int);
void stopRAM(RAM*);

#endif // !MEMORY_H