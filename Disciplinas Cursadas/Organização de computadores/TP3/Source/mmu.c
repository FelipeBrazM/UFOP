#include "mmu.h"
#include <stdio.h>
#include <math.h>

bool canOnlyReplaceBlock(Line line) {
    // Or the block is empty or
    // the block is equal to the one in memory RAM and can be replaced
    if (line.tag == INVALID_ADD || (line.tag != INVALID_ADD && !line.updated))
        return true;
    return false;
}


int memoryCacheMapping(int address, Cache* cache) {   

    #if defined MAPEAMENTO_ASSOCIATIVO 

        for(int i=0; i<cache->size; i++){
            //Varre a cache, procurando a tag que contem o endereco desejado
            if(address == cache->lines[i].tag){
                return i;
            }
        }
        return 0;
    
    #endif
}

int memoryRAMMapping(int address, RAM *ram){
    for(int i = 0; i < ram->size; i++){
        if(address == ram->blocks[i].enderecoEmDisco) //caso o endereco passado seja igual a tag do bloco da ram, retorna a posicao no vetor de memoryblocks
            return i;
    }

    return 0;
}

int blocoSairDaRam(RAM *ram){
    #ifdef LFU
        int pos = rand() % ram->size;
        MemoryBlock menor = ram->blocks[pos];

        for(int i = 0; i < ram->size; i++){
            if(menor.count > ram->blocks[i].count){
                menor = ram->blocks[i];
                pos = i;
            }
        }

        return pos;
    #endif

    #ifdef FIFO
        MemoryBlock maior = ram->blocks[0];
        int pos = 0;

        for(int i = 0; i < ram->size;i++){
            if(maior.count > ram->blocks[i].count){
                maior = ram->blocks[i];
                pos = i;
            }
        }

        return pos;
    #endif

    #ifdef RANDOM
        return rand() % ram->size;
    #endif
}

//Varre o vetor de linhas da cache 
int procurarBlocoASair(Cache* cache){

    #ifdef MAPEAMENTO_DIRETO
        return address % cache->size;
    #endif

    int posicao = 0;

    //Verificando se há posições vazias na cache. Caso tenha, retorna a posição vazia
    #ifndef RANDOM
        for(int i = 0; i < cache->size; i++){
            if(cache->lines[i].tag == -1)
                return i;
        }
    #endif

    //Procura a linha com o menor numero de utilizacoes - LFU
    #ifdef LFU
        
        Line menosUsada = cache->lines[0];
        for(int i = 1; i < cache->size; i++){
            if(cache->lines[i].contador < menosUsada.contador){
                menosUsada = cache->lines[i];
                posicao = i;
            }
        }
        
    #endif

    //Procura a linha com o maior numero de utilizacoes - LRU
    //Procura a linha com o maior tempo na cache - FIFO
    #if defined LRU || defined FIFO
    
        Line maisUsado = cache->lines[0];
        for(int i = 1; i < cache->size; i++){
            if(cache->lines[i].contador > maisUsado.contador){
                maisUsado = cache->lines[i];
                posicao = i;
            }
        }

    #endif

    //Gera uma posicao aleatoria da cache para ser removida
    #ifdef RANDOM
        posicao = rand() % (cache->size);
    #endif

    return posicao;
}

#if defined LFU || defined LRU || defined FIFO
    void reiniciaContador(Cache* cache, int posLinha){
        cache->lines[posLinha].contador = 0;
    }
#endif

#if defined LRU || defined FIFO 
    void adicionarMaisUmNoContador(Cache * cache, int posUsado){
        //Incrementando mais um em todas os contadores das linhas
        for(int i = 0; i < cache->size; i++){
            if(cache->lines[i].tag != INVALID_ADD)
            cache->lines[i].contador++;
        }
        
        #ifdef LRU
            //Colocando a linha atual como zero
            cache->lines[posUsado].contador = 0;
        #endif
    }

    void adicionaMaisUmNoContadorRAM(MemoryBlock* RAM, int n){
        for(int i = 0; i < n; i++){
            RAM[i].count++;
        }
    }
    

#endif

void reiniciaContadorRam(int *contador){
    *contador = 0;
}

void updateMachineInfos(Machine* machine, int hitMiss, int cost) {
    switch (hitMiss) {
        case 1:
            machine->hitL1 += 1;
            break;

        case 2:
            machine->hitL2 += 1;
            machine->missL1 += 1;
            break;

        case 3:
            machine->missL1 += 1;
            machine->missL2 += 1;
            machine->hitL3 += 1;
            break;
        
        case 4:
            machine->hitRAM += 1;
            machine->missL1 += 1;
            machine->missL2 += 1;
            machine->missL3 += 1;
            break;

        case 5:
            machine->missL1 += 1;
            machine->missL2 += 1;
            machine->missL3 += 1;
            machine->missRAM += 1;
            machine->hitDisk += 1;
            break;
    }
    machine->totalCost += cost;
}

void atualizaDisco(MemoryBlock *ram){
    FILE *arquivo = fopen("disk.dat", "rb");
    MemoryBlock disco[DISK_SIZE];
    for (int i = 0; i < DISK_SIZE; i++)
    {
        int id;
        int v[WORDS_SIZE];
        fread(&id, sizeof(int), 1, arquivo);
        fread(v, sizeof(int), WORDS_SIZE, arquivo);
        disco[i].enderecoEmDisco = id;

        for (int j = 0; j < WORDS_SIZE; j++)
            disco[i].words[j] = v[j];
    
    }

    fclose(arquivo);

    arquivo = fopen("diskTemp.dat", "wb");
    //grava todos os registros anteriores ao que sera alterado
    for(int i = 0; i < ram->enderecoEmDisco; i++){
        fwrite(&disco[i].enderecoEmDisco, sizeof(int), 1, arquivo);
        fwrite(disco[i].words, sizeof(int), WORDS_SIZE, arquivo);
    }

    //grava o novo registro
    fwrite(&ram->enderecoEmDisco, sizeof(int), 1, arquivo);
    fwrite(ram->words, sizeof(int), WORDS_SIZE, arquivo);

    //grava os demais registros
    for (int i = ram->enderecoEmDisco + 1; i < DISK_SIZE; i++){
        fwrite(&disco[i].enderecoEmDisco, sizeof(int), 1, arquivo);
        fwrite(disco[i].words, sizeof(int), WORDS_SIZE, arquivo);
    }

    rename("diskTemp.dat", "disk.dat");

    fclose(arquivo);
}

int verificaRamDisco(MemoryBlock *ram, Address address, int *ramPos, RAM *ramMachine){
    
    //Caso em que o endereço está na ram
    if(ramMachine->blocks[*ramPos].enderecoEmDisco == address.block){
        ramMachine->blocks[*ramPos].count++; //Acresecentando mais um no contador sempre que o valor for utilizado
        return 4; //Informa que teve de acessar a ram somente
    }

    //Caso em que o endereço está no disco
    *ramPos =  blocoSairDaRam(ramMachine); //Posição do bloco que saiŕa da ram

    //Armazenando bloco que sairá da ram
    MemoryBlock aux;
    aux.count = ramMachine->blocks[*ramPos].count;
    aux.enderecoEmDisco = ramMachine->blocks[*ramPos].enderecoEmDisco;

    for (int j = 0; j < WORDS_SIZE; j++)
        aux.words[j] = ramMachine->blocks[*ramPos].words[j];
    
    //Obtendo endereço do disco
    FILE *arq = fopen("disk.dat", "rb");
    int id;
    int v[WORDS_SIZE];
    for(int i = 0; i <= address.block; i++){
        fread(&id, sizeof(int), 1, arq);
        fread(v, sizeof(int), WORDS_SIZE, arq);
    }

    fclose(arq);

    //Passando do disco para ram
    ram[*ramPos].enderecoEmDisco = address.block;
    for (int i = 0; i < WORDS_SIZE; i++)
        ram[*ramPos].words[i] = v[i];

    //Passando o bloco que sairá da RAM para o disco
    FILE *arq2 = fopen("disk.dat", "ab+");
    
    int idAux;
    int vAux[WORDS_SIZE];

    for (int i = 0; i < address.block; i++){
        fread(&idAux, sizeof(int), 1, arq2);
        fread(vAux, sizeof(int), WORDS_SIZE, arq2);    
    }
    fwrite(&aux.enderecoEmDisco, sizeof(int), 1, arq2);
    fwrite(aux.words, sizeof(int), WORDS_SIZE, arq2);

    fclose(arq2);

    return 5; //Informa que teve de acessar o disco
}

Line* MMUSearchOnMemorys(Address add, Machine* machine) {
    // Strategy => write back
    
    // Mapeamento da memoria
    int l1pos = memoryCacheMapping(add.block, &machine->l1);
    int l2pos = memoryCacheMapping(add.block, &machine->l2);
    int l3pos = memoryCacheMapping(add.block, &machine->l3);
    int ramPos = memoryRAMMapping(add.block, &machine->ram);
    
    MemoryBlock* RAM = machine->ram.blocks;
    Line* cache1 = machine->l1.lines;
    Line* cache2 = machine->l2.lines;
    Line* cache3 = machine->l3.lines;

    //Adiciona mais um no tempo de vida de todos os valores da cache
    #ifdef FIFO
        adicionarMaisUmNoContador(&machine->l1, l1pos);
        adicionarMaisUmNoContador(&machine->l2, l2pos);
        adicionarMaisUmNoContador(&machine->l3, l3pos);
        adicionaMaisUmNoContadorRAM(RAM, machine->ram.size);
    #endif

    if (cache1[l1pos].tag == add.block) { 
        /* Block is in memory cache L1 */
        cache1[l1pos].cost = COST_ACCESS_L1;
        cache1[l1pos].cacheHit = 1;
        
        #ifdef LFU
            cache1[l1pos].contador += 1;
        #endif
    } 
    else if (cache2[l2pos].tag == add.block) { 
        /* Block is in memory cache L2 */
        cache2[l2pos].cost = COST_ACCESS_L1 + COST_ACCESS_L2;
        cache2[l2pos].cacheHit = 2;
        
        #ifdef LFU
            cache2[l2pos].contador += 1;
        #endif

        updateMachineInfos(machine, cache2[l2pos].cacheHit, cache2[l2pos].cost);

        #ifdef CAN_BE_IMPROVED

            //Levando da cache 2 para a cache 1
            int posL1 = procurarBlocoASair(&machine->l1);
            Line leaveL1 = cache1[posL1];

            cache1[posL1] = cache2[l2pos];
            cache2[l2pos] = leaveL1;        

            #ifndef RANDOM 
                reiniciaContador(&machine->l2, l2pos);
                reiniciaContador(&machine->l1, l1pos);
            #endif

            return &(cache1[l1pos]); 

        #endif
        
        #ifndef CAN_BE_IMPROVED

            return &(cache2[l2pos]); 

        #endif
    } 
    else if(cache3[l3pos].tag == add.block){

        cache3[l3pos].cost = COST_ACCESS_L1 + COST_ACCESS_L2 + COST_ACCESS_L3;
        cache3[l3pos].cacheHit = 3; 
        
        #ifdef LFU
            cache3[l3pos].contador += 1;
        #endif

        #ifdef LRU
            adicionarMaisUmNoContador(&machine->l3, l3pos);
        #endif

        updateMachineInfos(machine, cache3[l3pos].cacheHit, cache3[l3pos].cost);
        return &(cache3[l3pos]);
    } 
    else if(RAM[ramPos].enderecoEmDisco == add.block){
                
        atualizaDisco(&(RAM[ramPos]));

        l3pos = procurarBlocoASair(&machine->l3);
        
        for (int i = 0; i < WORDS_SIZE; i++) //passa as palavras para a l3
            cache3[l3pos].block.words[i] = RAM[ramPos].words[i];
        
        cache3[l3pos].tag = RAM[ramPos].enderecoEmDisco;
        
        #ifdef LFU
            cache3[l3pos].contador += 1;
            RAM[ramPos].count +=1;
        #endif

        cache3[l3pos].cacheHit = 4;
        cache3[l3pos].cost = COST_ACCESS_L1 + COST_ACCESS_L2 + COST_ACCESS_L3 + COST_ACCESS_RAM;
        updateMachineInfos(machine, cache3[l3pos].cacheHit, cache3[l3pos].cost);
        return &(cache3[l3pos]);
        
    }
    else { 
        
        //Procurando os blocos que podem sair de cada linha
        l1pos = procurarBlocoASair(&machine->l1);
        l2pos = procurarBlocoASair(&machine->l2);
        l3pos = procurarBlocoASair(&machine->l3);
        ramPos = blocoSairDaRam(&machine->ram);
        int cacheHit = 4;
        
        
        if (!canOnlyReplaceBlock(cache1[l1pos])) { 
            /* The block on cache L1 cannot only be replaced, the memories must be updated */
            if (!canOnlyReplaceBlock(cache2[l2pos])) {
                
                if (!canOnlyReplaceBlock(cache3[l3pos])) {

                    //Se a informação nao estiver na RAM, ela vai trocar o valor da Ram com o do disco
                    cacheHit = verificaRamDisco(RAM, add, &ramPos, &(machine->ram));

                    //Sai um valor da RAM para receber quem esta na L3
                    int ramposWillBeRemoved = blocoSairDaRam(&(machine->ram));

                    //Passa as informações do L3 para a RAM e reinicia o contador da RAM
                    RAM[ramposWillBeRemoved].enderecoEmDisco = cache3[l3pos].tag;
                    for (int i = 0; i < WORDS_SIZE; i++)
                        RAM[ramposWillBeRemoved].words[i] = cache3[l3pos].block.words[i];

                    reiniciaContadorRam(&RAM[ramposWillBeRemoved].count);

                }
                cache3[l3pos] = cache2[l2pos];
                #if defined LFU || defined LRU || defined FIFO
                    reiniciaContador(&machine->l3, l3pos);
                #endif 

            }
            cache2[l2pos] = cache1[l1pos]; //cache 1 pra cache2
            #if defined LFU || defined LRU || defined FIFO
                reiniciaContador(&machine->l2, l2pos);
            #endif 
        }

        cacheHit = verificaRamDisco(RAM, add, &ramPos, &(machine->ram));

        //Custo de acessp as memórias
        int costAcess;
        if(cacheHit == 4)
            costAcess = COST_ACCESS_L1 + COST_ACCESS_L2 + COST_ACCESS_L3 + COST_ACCESS_RAM;
        else
            costAcess = COST_ACCESS_L1 + COST_ACCESS_L2 + COST_ACCESS_L3 + COST_ACCESS_RAM + COST_ACCESS_DISK;

        //passa da ram para l1
        for (int i = 0; i < WORDS_SIZE; i++) //passa as palavras para a l3
            cache1[l1pos].block.words[i] = RAM[ramPos].words[i];
        
        //passa a tag da ram para l1
        cache1[l1pos].tag = RAM[ramPos].enderecoEmDisco;

        cache1[l1pos].tag = add.block;
        cache1[l1pos].updated = false;
        cache1[l1pos].cost = costAcess;
        cache1[l1pos].cacheHit = cacheHit;
        
        #if defined LFU || defined LRU || defined FIFO
            reiniciaContador(&machine->l1, l1pos);
        #endif 
    }
    updateMachineInfos(machine, cache1[l1pos].cacheHit, cache1[l1pos].cost);
    return &(cache1[l1pos]);
}
