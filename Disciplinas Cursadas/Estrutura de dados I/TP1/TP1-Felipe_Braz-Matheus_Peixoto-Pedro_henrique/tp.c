//Felipe Braz Marques - Matheus Peixoto Ribeiro Vieira - Pedro Henrique Rabelo Leao de Oliveira
#include "automato.h"

int main(){

    AutomatoCelular automato;

    scanf("%d", &automato.dimensoes);

    alocarReticulado(&automato.reticulado, automato.dimensoes);

    preencherReticulado(&automato);

    evoluirReticulado(&automato);

    imprimeReticulado(automato);

    desalocarReticulado(&automato.reticulado, automato.dimensoes);

    return 0;
}