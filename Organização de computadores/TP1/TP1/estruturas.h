#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Definicoes para Acesso Indexado, Arvore binaria de pesquisa e Arvore B
#define M 2
#define MM 4

typedef long TipoChave;

typedef struct TipoRegistro{
    TipoChave Chave;
    long dado1;
    char dado2[26];
    char dado3[101];
} TipoRegistro;

typedef struct TipoPagina* TipoApontador;

typedef struct TipoPagina {
    short n;
    TipoRegistro r[MM];
    TipoApontador p[MM + 1];
} TipoPagina;

//Definicoes para a arvore B estrela
#define MB 2
#define MMB 2*MB

#define MB2 2
#define MMB2 2*MB2

typedef struct TipoPaginaEstrela* TipoApontadorEstrela;

typedef TipoRegistro TipoRegistroEstrela;

typedef enum {Interna, Externa} TipoIntExt;

typedef struct TipoPaginaEstrela{ 
    TipoIntExt Pt; 
    union {
        struct { 
            int ni; 
            TipoChave ri[MMB]; 
            TipoApontadorEstrela pi[MMB + 1];
        } U0; 
        struct { 
            int ne; 
            TipoRegistroEstrela re[MMB2];
        } U1;
    } UU;
} TipoPaginaEstrela;


//Definicoes para uma pesquisa
typedef struct{
    int comparacoes;
    int transferencias;
}Quantidades;

typedef struct Resultados{

    clock_t tempoPreProcessamento[2], tempoPesquisa[2];
    
    TipoRegistro pesquisar;
    TipoRegistroEstrela pesquisarEstrela; 

    Quantidades preProcessamento;
    Quantidades pesquisa;
    
    int metodo;
    int resultadoPesquisa;

    double tempoPreProcessamentCalculado;
    double tempoPesquisaCalculado;
    double tempoTotalCalculado;

    bool exibirChaves;

}Resultados;


#endif