#include <stdio.h>
#include <stdlib.h>
#include "../estruturas.h"

void trocaPosicao(TipoRegistro* registros, int * i, int * j){
    TipoRegistro auxiliar;

    auxiliar = registros[*i];
    registros[*i] = registros[*j];
    registros[*j] = auxiliar;
    *i += 1;
    *j -= 1;

}

void ordenaNota(TipoRegistro * registros, int inicio, int fim){
    int i, j;
    TipoRegistro pivo; 

    i = inicio;
    j = fim;
    pivo = registros[(inicio + fim) / 2];

    while (i <= j){
        while (registros[i].nota < pivo.nota && i < fim)
            i++;
        
        while (registros[j].nota > pivo.nota && j > inicio)
            j--;

        if (i <= j)
            trocaPosicao(registros, &i, &j);
    }

    if (j > inicio)
        ordenaNota(registros, inicio, j);

    if (i < fim)
        ordenaNota(registros, i, fim);
}


int main(int argc, char const *argv[])
{
    FILE *arq = fopen("../PROVAO.TXT", "r");
    if(arq == NULL){
        printf("Error: Cannot open file\n"); return 0;
    }

    int numAlunos = 471705;
    TipoRegistro *alunos = (TipoRegistro*) malloc (numAlunos * sizeof(TipoRegistro));

    for (int i = 0; i < numAlunos; i++){
        fscanf(arq, "%d %lf", &alunos[i].Chave, &alunos[i].nota);
        fgets(alunos[i].estado, 2, arq);
        fgets(alunos[i].cidade, 50, arq);
        fgets(alunos[i].curso, 30, arq);
    }
    fclose(arq);
    
    // for (int i = 0; i < numAlunos; i++){
    //     printf("%d %lf %s %s %s\n", alunos[i].Chave, alunos[i].nota, alunos[i].estado, alunos[i].cidade, alunos[i].curso);
    // }
    
    FILE *arq2 = fopen("../PROVAO_ALEATORIO.bin", "wb");
    fwrite(alunos, sizeof(TipoRegistro), numAlunos, arq2);
    fclose(arq2);

    printf("Ordenando.\n");
    ordenaNota(alunos, 0, numAlunos-1);

    //Gerando o arquivo ordenado de forma crescente
    FILE *arqCrescente = fopen("../PROVAO_CRESCENTE.bin", "wb");
    fwrite(alunos, sizeof(TipoRegistro), numAlunos, arqCrescente);
    fclose(arqCrescente);

    //Gerando o arquivo ordenado de forma decrescente
    TipoRegistro temp;
    for(int i = 0; i < numAlunos/2; i++){
        temp = alunos[i];
        alunos[i] = alunos[numAlunos-i-1];
        alunos[numAlunos-i-1] = temp;
    }
    FILE *arqDecrescente = fopen("../PROVAO_DECRESCENTE.bin", "wb");
    fwrite(alunos, sizeof(TipoRegistro), numAlunos, arqDecrescente);
    fclose(arqDecrescente);

    free(alunos);
    return 0;
}
