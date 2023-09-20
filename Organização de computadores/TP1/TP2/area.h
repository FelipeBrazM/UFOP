#ifndef AREA_H
#define AREA_H

#include "estruturas.h"
#include "ordenacao.h"

#define TAMAREA  20

typedef struct TipoArea{
    TipoRegistro area [TAMAREA];
    int n;
}TipoArea;

TipoArea inicializaArea();

void InsereItem(TipoRegistro UltLido, TipoArea *Area, InfoOrdenacao*);

int ObterNumCelOcupadas(TipoArea * area);

void RetiraUltimo(TipoArea * area, TipoRegistro * R);

void RetiraPrimeiro(TipoArea * area, TipoRegistro * R);

void ordenaArea(TipoRegistro * registros, int inicio, int fim);

void trocaPosicao(TipoRegistro* registros, int * i, int * j);

#endif