#ifndef MENUS_H
#define MENUS_H

#include "acesso_indexado.h"
#include "abp.h"
#include "arvore_b.h"
#include "arvore_b_estrela.h"


bool verificaInputsValidos(int, int, int);

char * verificaSituacao(int);

char * geraNomeArquivo(char *, int, char * );

long converteChave(char * );

int selecionaMetodo(int, long, char *, int, Resultados * );

void imprimeResultados(Resultados * );

bool verificaChaveRepetida(int, int *, int );

bool gerarNumerosAleatorios(char *, int , Resultados *);

void realizarPesquisa(Resultados *, long, char *, int );

void calculaMediaExecucoes(Resultados *);

#endif