#ifndef HASH
#define HASH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define N 21 // tamanho da chave ( string )
#define D 51 // tamanho do nome do documento ( string )
#define ND 100 // numero maximo de documentos
#define NN 1000 // numero maximo de chaves por documentos
#define M 1000 // tamanho da tabela
#define MAX_STR 20001

typedef char Chave[N];
typedef char NomeDocumento[D];

int h(char*, int);
int pegarChaves(Chave*);

#endif // !HASH
