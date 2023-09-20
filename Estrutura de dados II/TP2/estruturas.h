#ifndef ESTRTURAS_H
#define ESTRTURAS_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>
#include <time.h>

typedef int TipoChave;

//Struct correspondente a estrutura do arquivo
typedef struct{
    TipoChave Chave;
    double nota; //Com o float, os dados estavam incorretos. Ex: 34.8 sendo lido como 34.799999...
    char estado[3];
    char cidade[51];
    char curso[31];
}TipoRegistro;

//geracao de blocos por substituicao
typedef struct {
    TipoRegistro registro;
    bool marcado; //o registro fica marcado ao entrar na memoria quando ele e menor que o ultimo a sair
} RegistroParaSubstituicao;

enum TipoFita {ENTRADA = 1, SAIDA = 2};
typedef struct{
    int n_blocos;
    int * qtdItensBloco;
    FILE * arq;
    enum TipoFita tipo;
}Fita;

//para controlar as fitas de entrada durante o processo de intercalacao
typedef struct{
    int qtdItensLidos;
    TipoRegistro dadoLido;
    bool fitaAtiva;
}Intercalacao;

typedef struct{
    int qtdLeitura;
    int qtdLeituraGeracaoBlocos;
    int qtdEscrita;
    int qtdEscritaGeracaoBlocos;

    int qtdLeituraBinTxt;
    int qtdEscritaBinTxt;

    int comparacoesChave;

    clock_t horarioInicio;
    clock_t horarioFim;

}AcessosArquivos;


enum Metodo {BALANCEADA_BLOCO_OI = 1, BALANCEADA_HEAP = 2, QUICKSORT = 3};
enum Situacao {ASCENDENTE = 1, DESCENDENTE = 2, DESORDENADO = 3};

typedef struct{
    enum Metodo metodo;
    int quantidade;
    enum Situacao situacao;
    bool p;
    char nomeArquivo[50];
    AcessosArquivos acessos;
}InfoOrdenacao;


#endif