#include "ordenacao.h"

struct ponto{
    int x;
    int y;
};

struct trajeto{
    Ponto* pontos;
    char nome[25];
    float deslocamentoTotal;
    float distanciaTotal;
};

Ponto* alocaPontos(int n){
    Ponto * pontos = (Ponto*) malloc(n * sizeof(Ponto));
    return pontos;
}

void desalocaPontos(Ponto* ponto){
    free(ponto);
}

Trajeto* alocaTrajetos(int n){
    Trajeto* trajetos = (Trajeto*) malloc(n * sizeof(Trajeto));

    if(trajetos == NULL){
        printf("Erro na alocacao dos trajetos\n");
        exit(1);
    }
    return trajetos;
}

void desalocaTrajeto(Trajeto** trajetos, int qtdTrajetos, int qtdPontos){
    for(int i = 0; i<qtdTrajetos; i++){
        desalocaPontos( (*trajetos)[i].pontos);
    }
    free(*trajetos);
}

void lerTrajetos(int qtdTrajetos, int qtdPontos, Trajeto* trajetos){
    
    for(int i = 0; i < qtdTrajetos; i++){
        scanf("%s", trajetos[i].nome);
        getchar();

        trajetos[i].pontos = alocaPontos(qtdPontos);
        
        for(int j = 0; j < qtdPontos; j++){
            scanf("%d", &trajetos[i].pontos[j].x);
            scanf("%d", &trajetos[i].pontos[j].y);
        }
    }
    
}

float calcularDeslocamentoParcial(Ponto inicio, Ponto fim){
    //Calcula o deslocamento entre dois pontos quaisquer. Sejam eles para o calculo de deslocamento ou para os pontos das distancias
    float deslocamento = sqrt(
        pow(fim.x - inicio.x  ,2) +
        pow(fim.y - inicio.y   ,2)
    );
    return (float) deslocamento; 
}

void calcularDistancia(Trajeto* trajetos, int index, int qtdPontos){
    float distancia = 0;
    
    for(int i = 0; i < qtdPontos-1; i++){
        //Calculando o deslocamento entre dois pontos e somando na distancia final
        distancia += calcularDeslocamentoParcial(trajetos[index].pontos[i], trajetos[index].pontos[i+1]);
    }

    trajetos[index].distanciaTotal = roundf(distancia * 100) / 100; //Arredondando para duas casa decimais
}

void calcularDeslocamento(Trajeto* trajetos, int index, int qtdPontos){
    //Calcula o deslocamento entre o ponto final e inicial;
    trajetos[index].deslocamentoTotal = calcularDeslocamentoParcial( trajetos[index].pontos[0], trajetos[index].pontos[qtdPontos - 1]);
}

void trocaPosicao(Trajeto* trajetos, int * i, int * j){
    Trajeto auxiliar;

    auxiliar = trajetos[*i];
    trajetos[*i] = trajetos[*j];
    trajetos[*j] = auxiliar;
    *i += 1;
    *j -= 1;

}

void ordenaDistancia(Trajeto * trajetos, int inicio, int fim){
    int i, j;
    Trajeto pivo; 

    i = inicio;
    j = fim;
    pivo = trajetos[(inicio + fim) / 2];

    while (i <= j){
        while (trajetos[i].distanciaTotal > pivo.distanciaTotal && i < fim)
            i++;
        
        while (trajetos[j].distanciaTotal < pivo.distanciaTotal && j > inicio)
            j--;

        if (i <= j)
            trocaPosicao(trajetos, &i, &j);
    }

    if (j > inicio)
        ordenaDistancia(trajetos, inicio, j);

    if (i < fim)
        ordenaDistancia(trajetos, i, fim);
}

void ordenaDeslocamento(Trajeto * trajetos, int inicio, int fim){
    int i, j;
    Trajeto pivo; 

    i = inicio;
    j = fim;
    pivo = trajetos[(inicio + fim) / 2];

    while (i <= j){
        while (trajetos[i].deslocamentoTotal < pivo.deslocamentoTotal && i < fim)
            i++;
        
        while (trajetos[j].deslocamentoTotal > pivo.deslocamentoTotal && j > inicio)
            j--;

        if (i <= j)
            trocaPosicao(trajetos, &i, &j);
    }

    if (j > inicio)
        ordenaDeslocamento(trajetos, inicio, j);

    if (i < fim)
        ordenaDeslocamento(trajetos, i, fim);
}

void ordenaNome(Trajeto * trajetos, int inicio, int fim){
    int i, j;
    Trajeto pivo; 

    i = inicio;
    j = fim;
    pivo = trajetos[(inicio + fim) / 2];

    while (i <= j){
        while (strcmp(trajetos[i].nome, pivo.nome) < 0 && i < fim)
            i++;
        
        while (strcmp(trajetos[j].nome, pivo.nome) > 0 && j > inicio)
            j--;

        if (i <= j)
            trocaPosicao(trajetos, &i, &j);
    }

    if (j > inicio)
        ordenaNome(trajetos, inicio, j);

    if (i < fim)
        ordenaNome(trajetos, i, fim);
}

void ordernacao(Trajeto * trajetos, int qtdTrajetos){

   //Ordenando por ordem decrescente da distancia percorrida
    ordenaDistancia(trajetos, 0, qtdTrajetos - 1);

    //Verificando se ha distancias iguais e ordenando o deslocamento
    for(int i = 0; i < qtdTrajetos-1; i++){
        
        if(trajetos[i].distanciaTotal == trajetos[i+1].distanciaTotal){
            //Verificando ate qual trajeto vai essa igualdade
            int fim = i;
            while(fim < qtdTrajetos && trajetos[i].distanciaTotal == trajetos[fim].distanciaTotal){
                fim++;
            }

            fim--;

            //Ordenando pelo deslocamento
            ordenaDeslocamento(trajetos, i, fim);
            i = fim;
        }

    }

   //Verificando o deslocamento e distancia para ordenar pelo nome
    for(int i = 0; i < qtdTrajetos-1; i++){
        
        if(trajetos[i].distanciaTotal == trajetos[i+1].distanciaTotal && trajetos[i].deslocamentoTotal == trajetos[i+1].deslocamentoTotal){
            //Verificando até qual trajeto vai essa igualdade
            int fim = i;
            while(fim < qtdTrajetos && trajetos[i].distanciaTotal == trajetos[fim].distanciaTotal && trajetos[i].deslocamentoTotal == trajetos[fim].deslocamentoTotal){
                fim++;
            } 

            fim--;

            //Ordenando pelo deslocamento
            ordenaNome(trajetos, i, fim);
            i = fim;
        }

    }


}

void imprime(Trajeto * trajetos, int qtdTrajetos){
    for(int i = 0; i < qtdTrajetos; i++){
        printf("%s %.2f %.2f\n", trajetos[i].nome, trajetos[i].distanciaTotal, trajetos[i].deslocamentoTotal);
    }
}

