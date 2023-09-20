#ifndef __QUICKSORT__
#define __QUICKSORT__

#include "estruturas.h"
#include "area.h"

#include "quickSort.h"

void quickSort(InfoOrdenacao * infoOrdenacao);

void QuicksortExterno(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir, InfoOrdenacao * infoOrdenacao);

//Le o dado do arquivo superior
void LeSup(FILE **ArqLEs, TipoRegistro *UltLido, int *Ls, short *OndeLer, InfoOrdenacao * infoOrdenacao);
//Le o dado do arquivo inferior
void LeInf(FILE **ArqLi, TipoRegistro *UltLido, int *Li, short *OndeLer, InfoOrdenacao * infoOrdenacao);

void InserirArea(TipoArea *Area, TipoRegistro *UltLido, int *NRArea, InfoOrdenacao *);

//Escreve o item no arquivo superior
void EscreveMax(FILE **ArqLEs, TipoRegistro R, int *Es, InfoOrdenacao * infoOrdenacao);

//Escreve o item no arquivo inferior
void EscreveMin(FILE **ArqEi, TipoRegistro R, int *Ei, InfoOrdenacao * infoOrdenacao);

//Remove o maior valor do pivo
void RetiraMax(TipoArea *Area, TipoRegistro *R, int *NRArea);

//Remove o menor valor do pivo
void RetiraMin(TipoArea *Area, TipoRegistro *R, int *NRArea);

void Particao(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, TipoArea Area, int Esq, int Dir, int *i, int *j, InfoOrdenacao * infoOrdenacao);


#endif
