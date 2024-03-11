//Felipe Braz Marques 22.1.4030

#ifndef FUNCTION_H 
#define FUNCTION_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_RESET            "\x1b[0m"
#define ANSI_COLOR_BLACK      "\x1b[30m"
#define ANSI_COLOR_RED        "\x1b[31m"
#define ANSI_COLOR_GREEN      "\x1b[32m"
#define ANSI_COLOR_YELLOW     "\x1b[33m"
#define ANSI_COLOR_BLUE       "\x1b[34m"
#define ANSI_COLOR_MAGENTA    "\x1b[35m"
#define ANSI_COLOR_CYAN       "\x1b[36m"
#define ANSI_COLOR_WHITE      "\x1b[37m"

#define ANSI_BG_COLOR_BLACK   "\x1b[40m"
#define ANSI_BG_COLOR_RED     "\x1b[41m"
#define ANSI_BG_COLOR_GREEN   "\x1b[42m"
#define ANSI_BG_COLOR_YELLOW  "\x1b[43m"
#define ANSI_BG_COLOR_BLUE    "\x1b[44m"
#define ANSI_BG_COLOR_MAGENTA "\x1b[45m"
#define ANSI_BG_COLOR_CYAN    "\x1b[46m"
#define ANSI_BG_COLOR_WHITE   "\x1b[47m"

#define BOLD(string)       ANSI_BOLD             string ANSI_RESET
#define RED(string)        ANSI_COLOR_RED        string ANSI_RESET
#define GREEN(string)      ANSI_COLOR_GREEN      string ANSI_RESET
#define YELLOW(string)     ANSI_COLOR_YELLOW     string ANSI_RESET

typedef struct{
    
    char nome[64];
    int vitoria;
    int empate;
    int derrota;

}Ranking;


void menuPrincipal();
void inicializarMatriz(char mat[][3]);
void printaMatriz(char mat[][3]);
void printTabuleiro(char mat[][3]);
void pegaJogadores(char *jog1, char *jog2, int numJogadores);
int verificaGanhador(char, char[][3]);
void antiWin(char mat[][3]);
char *pegarComando(int numJog, char *jog1, char *jog2, char mat[][3], int ultimoJog, int * linha, int *coluna, char jog[]);
void salvarJogo(int numJog, char *jog1, char *jog2, char mat[][3], int ultimoJog, char *str);
int abrirJogo(int *contaRodadas, int *numJog, char *jog1, char *jog2, char mat[][3], int *ultimoJog, char *str);
void zeraUsuario(Ranking *jog, char *nome);
int buscaJog(Ranking *lista, Ranking jog, int tamLista);
int compara(Ranking a, Ranking b);
void ordenaLista(Ranking *lista, int tamLista);
void arqConfig(Ranking **lista, int *tamLista);
Ranking* alocaLista(int tamLista);
void liberaLista(Ranking *lista);
Ranking* realocaLista(Ranking **lista, int *tamLista);
void attArqConfig(Ranking *lista, int tamLista);
void mostraRanking(Ranking *lista, int tamLista);














#endif