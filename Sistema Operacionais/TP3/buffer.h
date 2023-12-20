#ifndef BUFFER_H
#define BUFFER_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <queue>
#include <pthread.h>
#include <cstdlib>
#include <time.h>
#include <unistd.h>
#include <thread>
#include <chrono>

using namespace std;

class Buffer{
    int cheio;  // Capacidade máxima do buffer
    queue<int> buffer;  // Fila que representa o buffer compartilhado

    pthread_mutex_t mutex;  // Mutex para controlar o acesso ao buffer
    pthread_cond_t condicaoProdutor;  // Condição de espera do produtor
    pthread_cond_t condicaoConsumidor;  // Condição de espera do consumidor

    static int produzidos;  // Contador estático para o número total de itens produzidos
    static int consumidos;  // Contador estático para o número total de itens consumidos


public:
    Buffer(int capacidadeMaxima = 100);  // Construtor que inicializa o buffer com uma capacidade máxima

    // Métodos relacionados ao buffer
    void insertItem(int item);  // Insere um item no buffer
    int removeItem();  // Remove um item do buffer
    int bufferLen();  // Retorna o tamanho atual do buffer
    
    // Métodos relacionados ao mutex
    void down();  // Bloqueia o mutex
    void up();  // Libera o mutex

    // Métodos relacionados aos semáforos (condições)
    void downProdutor();  // Aguarda até que o buffer não esteja cheio para o produtor produzir
    void downConsumidor();  // Aguarda até que o buffer não esteja vazio para o consumidor consumir
    void upProdutor();  // Sinaliza ao produtor que o buffer não está mais cheio
    void upConsumidor();  // Sinaliza ao consumidor que o buffer não está mais vazio

    // Métodos relacionados ao produtor e consumidor
    void produzir(int item);  // Método do produtor para produzir e inserir um item no buffer
    void consumir(int & item);  // Método do consumidor para consumir e remover um item do buffer

    // Métodos para obter os contadores
    int getItensProduzidos();  // Retorna o número total de itens produzidos
    int getItensConsumidos();  // Retorna o número total de itens consumidos
};

class Consumidor{
    
    Buffer * buffer;  // Ponteiro para o buffer compartilhado
    int qtdItensConsumir;  // Número de itens que o consumidor deve consumir
    int consumoPorSegundo;  // Taxa de consumo em itens por segundo

public:
    Consumidor(Buffer * buffer, int qtdItensConsumir, int consumoPorSegundo);

    void run();  // Método que simula a execução do consumidor
};

class Produtor{
    
    Buffer * buffer;  // Ponteiro para o buffer compartilhado
    int qtdItensProduzir;  // Número de itens que o produtor deve produzir
    int itensPorSegundo;  // Taxa de produção em itens por segundo

public:
    Produtor(Buffer * buffer, int qtdItensProduzir, int itensPorSegundo);

    void run();  // Método que simula a execução do produtor
};

#endif
