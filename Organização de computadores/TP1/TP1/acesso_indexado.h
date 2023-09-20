#ifndef ACESSO_INDEXADO_H
#define ACESSO_INDEXADO_H

#include "estruturas.h"

#define ITENSPAGINA 10
#define MAXTABELA 100000

//definicao de uma entrada da tabela de indice das paginas
typedef struct{
    long chave;
} Indice;

bool pesquisa(Indice *, int, TipoChave, FILE *, Resultados *);
bool pesquisaBinaria(TipoRegistro *, TipoChave, TipoRegistro *, Resultados *, int);

int geraTabela(Indice *, FILE **, char *, Resultados *);

int acessoIndexado(char *, Resultados *);

#endif