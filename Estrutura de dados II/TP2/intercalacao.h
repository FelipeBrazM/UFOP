#include <math.h>
#include "estruturas.h"
#include "ordenacao.h"

void gerarFitas(Fita * fitas);

void fecharArquivos(Fita * fitas);

bool todosMarcados(RegistroParaSubstituicao* registros);

void desmarcarRegistros(RegistroParaSubstituicao* registros);

void atualizaStatusDeBlocos(Fita* fita, int numItensUltimoBloco);

int procuraMenor(RegistroParaSubstituicao* registros, int n, InfoOrdenacao*);

void gerarSelecaoSubstituicao(Fita * fitas, InfoOrdenacao *infoOrdenacao);

void gerarBlocos(Fita * fitas, InfoOrdenacao * infoOrdenacao);

void setPointeirosInicio(Fita * fitas);

Intercalacao * gerarFitasIntercalacao(int qtdFitas);

void tornarFitasAtivas(Intercalacao * dadosIntercalacao, int qtdFitas);

bool todosOsDadosLidos(Intercalacao * intercalacao, int qtdFitas);

//Le o primeiro item dos blocos e retorna a posicao do item de menor elemento
void lerPrimeirosDados(int inicio, Intercalacao * dadosIntercalacao, Fita * fitas, int qtdFitas, InfoOrdenacao * infoOrdenacao);

int procurarMenorValor(Intercalacao * dadosIntercalacao, int qtdFitas, InfoOrdenacao *infoOrdenacao);

void escreverDadosOrdenados(Fita * fitas, InfoOrdenacao * infoOrdenacao, int fitaSaida);

void intercalarBlocos(Fita * fitas, InfoOrdenacao * infoOrdenacao);

void intercalacao_balanceada(InfoOrdenacao * infoOrdenacao);