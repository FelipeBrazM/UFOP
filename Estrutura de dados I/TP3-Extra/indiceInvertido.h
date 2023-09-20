#ifndef HASH_ABERTO
#define HASH_ABERTO
// fazer funcao para dar free em tudo (mesma logica da de printar), 
//#define ANALISE_RELATORIO

#include "hash.h"

/* Os cabecalhos de todas as funcoes e os TADs podem ser alterados */

#define VAZIO " !!!!!!!!!!!!!!!!!!!!\0 "

typedef struct {
    int n; // numero de documentos
    Chave chave;
    NomeDocumento documentos[ND];
} Item;

typedef struct celula {
    struct celula *pProx;
    Item item;
} Celula;

typedef struct {
    Celula *pCabeca, *pUltimo;
} Lista;

typedef struct {
    int n; //numero de itens na hash
    Lista listas[M]; //array de listas com tamanho igual a M (1000)
} IndiceInvertido;

/* Funcoes tabela hash */
void inicia(IndiceInvertido *);
Celula * busca(IndiceInvertido *, Chave);
void removeDocumento(NomeDocumento *, int *, int);
int consulta(IndiceInvertido *, Chave*, int, NomeDocumento*, int *);
void imprimeIndiceInvertido(IndiceInvertido *);
void imprimeDocumentos(NomeDocumento*, int);
void liberaListas(IndiceInvertido *);

/* Funcoes Lista */
int listaInsereFinal(Lista *, Item);
int listaEhVazia(Lista *);
int listaRetiraPrimeiro (Lista *, Item *);
void listaEsvazia(Lista *pLista);

void sort(NomeDocumento*, int);

void leEntrada(IndiceInvertido *, int *);
bool insereDocumento(IndiceInvertido *, Chave, NomeDocumento);

void leOpcao(IndiceInvertido *, int);
void executaBuscaDoUsuario(IndiceInvertido *, int, char *);
void copiaPalavrasBuscadas(Chave *, int *, char *);

void merge(NomeDocumento*, int, int, int);
void mergeSort(NomeDocumento*, int, int);

#endif // !HASH_ABERTO
