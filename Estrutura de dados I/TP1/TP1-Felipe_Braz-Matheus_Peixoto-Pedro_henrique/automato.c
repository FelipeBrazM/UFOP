//Felipe Braz Marques - Matheus Peixoto Ribeiro Vieira - Pedro Henrique Rabelo Leao de Oliveira
#include "automato.h"

void alocarReticulado(int *** reticulado, int dimensoes){
    //Alocando dinamicamente o reticulado

    (*reticulado) = (int **) malloc(dimensoes * sizeof(int*));
    
    for(int i=0; i<dimensoes; i++)
        (*reticulado)[i] = (int *) malloc(dimensoes * sizeof(int));

}

void desalocarReticulado(int ***reticulado, int dimensoes){
    //Desalocando o reticulado

    for(int i=0; i<dimensoes; i++)
        free((*reticulado)[i]);

    free(*reticulado);

}

void preencherReticulado(AutomatoCelular* automato){
    //Preenche a matriz do reticulado com os dados lidos do usuario

    for(int i=0; i< automato->dimensoes; i++){
        
        for(int j=0; j< automato->dimensoes; j++){
            
            scanf("%d", &automato->reticulado[i][j]);
        
        }
    
    }

}

int verificaStatusCelula(int celulasVizinhasVivas, int statusDaCelula){
    
    //Caso a celula atual estiver viva
    if(statusDaCelula){
        if(celulasVizinhasVivas > 3 || celulasVizinhasVivas < 2)
            statusDaCelula = 0; //Morte por sufocamento ou solidao

    }
    //Caso a celula atual estiver mortas
    else{
        if(celulasVizinhasVivas == 3)
            statusDaCelula =  1;//Celula torna-se viva
    }
    
    return statusDaCelula;
}

void copiaMatriz(int** matrizOrigem, int** matrizDestino, int ordem){
    //Copia os dados da matrizOrigem para a matrizDestino

    for(int i=0; i<ordem; i++){
        
        for (int j = 0; j < ordem; j++){
            
            matrizDestino[i][j] = matrizOrigem[i][j];

        }
        
    }

}

void evoluirReticulado(AutomatoCelular* automato){

    //Matriz temporaria para armazenar os valores da proxima geracao do reticulado
    int ** reticuladoTemp;
    alocarReticulado(&reticuladoTemp, automato->dimensoes);

    int celulasVizinhasVivas;

    for(int i=0; i<automato->dimensoes; i++){
        //O limite da analise das linhas e colunas se da de uma linha e coluna anterior a principal e vai ate uma linha e coluna a mais que a principal

        //Verificando se esta na prmeira linha ou na ultima para nao acessar posicoes invalidas
        int linhaInicio = (i == 0) ? 0 : i-1;
        int linhaFinal = (i == (automato->dimensoes - 1)) ? (automato->dimensoes - 1) : i+1;

        for(int j=0; j<automato->dimensoes; j++){
        
            //Verificando se esta na prmeira coluna ou na ultima para nao acessar posicoes invalidas
            int colunaInicio = (j == 0) ? 0 : j-1;
            int colunaFinal = (j == automato->dimensoes - 1) ? (automato->dimensoes - 1) : j+1;

            celulasVizinhasVivas = 0;

            //Verificando quantas celulas vizinhas estao vivas
            for(int x = linhaInicio; x <= linhaFinal; x++){

                for(int y = colunaInicio; y <= colunaFinal; y++){

                    if(automato->reticulado[x][y] == 1)
                        celulasVizinhasVivas++;

                }

            }

            if(automato->reticulado[i][j] == 1)
                celulasVizinhasVivas--;//Removendo a celula do centro da contagem

            
            reticuladoTemp[i][j] = verificaStatusCelula(celulasVizinhasVivas, automato->reticulado[i][j]);

        }

    }
    //Transferindo os dados da matriz temporaria para a principal
    copiaMatriz(reticuladoTemp, automato->reticulado, automato->dimensoes);

    //Desalocando a matriz temporaria
    desalocarReticulado(&reticuladoTemp, automato->dimensoes);

}

void imprimeReticulado(AutomatoCelular automato){
    
    for(int i=0; i<automato.dimensoes; i++){

        for(int j=0; j<automato.dimensoes; j++){
            
            printf("%d ", automato.reticulado[i][j]);

        }

        printf("\n");

    }

}