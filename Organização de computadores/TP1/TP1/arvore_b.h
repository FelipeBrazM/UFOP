#ifndef ARVORE_B_H
#define ARVORE_B_H

#include <stdio.h>
#include <stdbool.h>
#include "cores.h"

#include "estruturas.h"

void inicializa(TipoApontador *);

bool pesquisa_arvore_b (TipoRegistro *, TipoApontador, Resultados *);

void imprime (TipoApontador);

void InsereNaPagina (TipoApontador, TipoRegistro, TipoApontador, Resultados *);

void Ins(TipoRegistro, TipoApontador, short *, TipoRegistro *, TipoApontador *, Resultados *);

void Insere(TipoRegistro, TipoApontador *, Resultados *);

int arvore_b(char *, int, Resultados *);

void liberaArvoreB(TipoApontador);

void exibirItens(TipoRegistro * registros, int quantidade);

#endif