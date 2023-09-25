#ifndef ORDENACAO_C
#define ORDENACAO_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct ponto Ponto;

typedef struct trajeto Trajeto;

Ponto* alocaPontos(int n);

void desalocaPontos(Ponto*);

Trajeto* alocaTrajetos(int n);

void desalocaTrajeto(Trajeto**, int, int);

void lerTrajetos(int, int, Trajeto*);

float calcularDeslocamentoParcial(Ponto, Ponto);

void calcularDistancia(Trajeto*, int, int);

void calcularDeslocamento(Trajeto*, int, int);

void trocaPosicao(Trajeto*, int*, int*);

void ordenaDistancia(Trajeto*, int, int);

void ordenaDeslocamento(Trajeto*, int, int);

void ordenaNome(Trajeto*, int, int);

void ordernacao(Trajeto *, int);

void imprime(Trajeto * trajetos, int qtdTrajetos);

#endif