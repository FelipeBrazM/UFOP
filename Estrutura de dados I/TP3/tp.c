#include "indiceInvertido.h"
#include <time.h>

int main() {

    #ifdef ANALISE_RELATORIO
        clock_t comeco, fim;
        double tempo_execucao;
        comeco = clock();
        int qtdColisoes = 0;
    #endif

    IndiceInvertido indiceInvertido;
    int nDocumentos;

    inicia(indiceInvertido);
    
    #ifdef ANALISE_RELATORIO
        leEntrada(indiceInvertido, &nDocumentos, &qtdColisoes);
    #else
        leEntrada(indiceInvertido, &nDocumentos);
    #endif
    
    leOpcao(indiceInvertido, nDocumentos);


    #ifdef ANALISE_RELATORIO
        fim = clock();
        tempo_execucao = ((double)(fim - comeco))/CLOCKS_PER_SEC;

        printf("\n\n===Informações da execução===\n");
        printColisoes(qtdColisoes);
        printf("Tempo de execução do programa: %lfs.\n", tempo_execucao);
        memoriaGasta(M*sizeof(Item), true);
    #endif

    return 0;
}
