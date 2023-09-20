#include "memory.h"
#include <stdio.h>

void startRAM(RAM * ram, int size){

    FILE * arquivo = fopen("disk.dat", "rb");

    if(arquivo == NULL){
        printf("Erro ao ler o arquivo\n");
        exit(1);
    }

    ram->blocks = (MemoryBlock *)calloc(size, sizeof(MemoryBlock));
    ram->size = size;
        
    for (int i = 0; i < size; i++){
        
        fread(&ram->blocks[i].enderecoEmDisco, sizeof(int), 1, arquivo);

        for (int j = 0; j < WORDS_SIZE; j++){
            fread(&ram->blocks[i].words[j], sizeof(int), 1, arquivo);
            
        }
    }

    fclose(arquivo);
}

void stopRAM(RAM *ram) {
    free(ram->blocks);
}


void startCache(Cache* cache, int size) {
    cache-> lines = (Line*) calloc(size, sizeof(Line));
    // cache->lines = (Line*) malloc(sizeof(Line) * size);
    cache->size = size;

    for (int i=0;i<size;i++)
        cache->lines[i].tag = INVALID_ADD;
}

void stopCache(Cache *cache) {
    free(cache->lines);
}

void iniciaDisco(){

    // Cria o arquivo binário
    FILE *arq;
    arq = fopen("disk.dat", "wb");

    // Gera o codigo do bloco e os números
    for (int i = 0; i < DISK_SIZE; i++){
        //Escreve o codigo do Bloco
        fwrite(&i, sizeof(int), 1, arq); 

        int v[WORDS_SIZE];
        for (int j = 0; j < WORDS_SIZE; j++){
            v[j] = rand() % 100;
            fwrite(&v[j], sizeof(int), 1, arq);
        }
    }

    fclose(arq);
}