//Felipe Braz Marques - Matheus Peixoto Ribeiro Vieira - Pedro Henrique Rabelo Leao de Oliveira

#ifndef AUTOMATO_H
#define AUTOMATO_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int ** reticulado;
    int dimensoes;
}AutomatoCelular;

void alocarReticulado(int ***, int);

void desalocarReticulado(int ***, int);

void preencherReticulado(AutomatoCelular*);

int verificaStatusCelula(int, int);

void copiaMatriz(int**, int**, int);

void evoluirReticulado(AutomatoCelular*);

void imprimeReticulado(AutomatoCelular);

#endif