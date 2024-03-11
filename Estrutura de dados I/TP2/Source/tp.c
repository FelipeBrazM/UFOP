#include "ordenacao.h"

int main(){

    int qtdTrajetos, qtdPontos;

    scanf("%d%d", &qtdTrajetos, &qtdPontos);

    Trajeto *trajetos = alocaTrajetos(qtdTrajetos);

    lerTrajetos(qtdTrajetos, qtdPontos, trajetos);

    //Calculando a distância e o deslocamento
    for(int i = 0; i<qtdTrajetos; i++){
        calcularDistancia(trajetos, i, qtdPontos);
        calcularDeslocamento(trajetos, i, qtdPontos);
    }

    ordernacao(trajetos, qtdTrajetos);

    imprime(trajetos, qtdTrajetos);

    desalocaTrajeto(&trajetos, qtdTrajetos, qtdPontos);

    return 0;
}