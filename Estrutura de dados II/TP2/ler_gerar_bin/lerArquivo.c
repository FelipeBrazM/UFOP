#include <stdio.h>
#include <stdlib.h>
#include "../estruturas.h"

int main(){
    int qtdAlunos = 100;
    //FILE *arq = fopen("../PROVAO_ALEATORIO.bin", "rb");
    FILE *arq = fopen("../fitas/fita_3.bin", "rb");
    //FILE *arq = fopen("Bloco_ord_interna-aleatorio-100.bin", "rb");
    
    TipoRegistro * alunos = malloc(qtdAlunos * sizeof(TipoRegistro));

    fread(alunos, sizeof(TipoRegistro), qtdAlunos, arq);

    for(int i = 0; i < qtdAlunos; i++){
        printf("%d %lf %s %s %s\n", alunos[i].Chave, alunos[i].nota, alunos[i].estado, alunos[i].cidade, alunos[i].curso);
    }
    
    free(alunos);
    fclose(arq);
}