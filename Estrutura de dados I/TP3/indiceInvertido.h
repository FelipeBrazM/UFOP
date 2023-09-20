#ifndef HASH_ABERTO
#define HASH_ABERTO

//#define ANALISE_RELATORIO

#include "hash.h"

/* Os cabecalhos de todas as funcoes e os TADs podem ser alterados */

#define VAZIO " !!!!!!!!!!!!!!!!!!!!\0 "

typedef struct {
    int n; // numero de documentos
    Chave chave;
    NomeDocumento documentos[ND];
} Item;

typedef Item IndiceInvertido[M];

/* Funcoes */
void inicia(IndiceInvertido);
int busca(IndiceInvertido, Chave);
void removeDocumento(NomeDocumento *, int *, int);
int consulta(IndiceInvertido, Chave*, int, NomeDocumento*, int *);
void imprimeIndiceInvertido(IndiceInvertido);
void imprimeDocumentos(NomeDocumento*, int);

void sort(NomeDocumento*, int);

#ifdef ANALISE_RELATORIO
    void leEntrada(IndiceInvertido, int *, int *);
    bool insereDocumento(IndiceInvertido, Chave, NomeDocumento, int *);
#else
    void leEntrada(IndiceInvertido, int *);
    bool insereDocumento(IndiceInvertido, Chave, NomeDocumento);
#endif

void leOpcao(IndiceInvertido, int);
void executaBuscaDoUsuario(IndiceInvertido, int, char *);
void copiaPalavrasBuscadas(Chave *, int *, char *);

void merge(NomeDocumento*, int, int, int);
void mergeSort(NomeDocumento*, int, int);

void printColisoes(int);
void memoriaGasta(long int memoria, bool exibir);

#endif // !HASH_ABERTO
