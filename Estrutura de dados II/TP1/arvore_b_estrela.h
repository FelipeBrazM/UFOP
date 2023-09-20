#ifndef ARVORE_B_ESTRELA
#define ARVORE_B_ESTRELA

#include "estruturas.h"
#include "stdbool.h"
#include <stdio.h>
#include <stdlib.h>
#include "cores.h"


void InsereNaPaginaExterna(TipoApontadorEstrela, TipoRegistroEstrela, Resultados *);

void InsereNaPaginaInterna(TipoApontadorEstrela, TipoChave, TipoApontadorEstrela, Resultados *);

void Ins_b_estrela(TipoRegistroEstrela, TipoApontadorEstrela, short *, TipoChave *, TipoApontadorEstrela* , Resultados *);

bool Pesquisa(TipoRegistroEstrela *, TipoApontadorEstrela *, Resultados *);

void Insere_b_estrela(TipoRegistroEstrela, TipoApontadorEstrela *, Resultados *);

void inicializa_b_estrela (TipoApontadorEstrela *);

int arvore_b_estrela(long, char *, int, Resultados *);

void printaArvore(TipoApontadorEstrela, int);

void liberaArvoreBEstrela(TipoApontadorEstrela);

void exibirItensArvoreBEstrela(TipoRegistroEstrela * registros, int quantidade);

#endif