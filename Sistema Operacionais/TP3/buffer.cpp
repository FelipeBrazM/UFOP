#include "buffer.h"

// Inicialização dos contadores estáticos
int Buffer::produzidos = 0;
int Buffer::consumidos = 0;

// Construtor da classe Buffer
Buffer::Buffer(int cheio) {
    this->cheio = cheio;

    // Inicialização do mutex e semáforos
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&condicaoProdutor, NULL);
    pthread_cond_init(&condicaoConsumidor, NULL);
}

// Método para inserir um item no buffer
void Buffer::insertItem(int item) {
    produzidos++;
    buffer.push(item);
}

// Método para remover um item do buffer
int Buffer::removeItem() {
    int item = buffer.front();
    buffer.pop();
    consumidos++;
    return item;
}

// Retorna o tamanho atual do buffer
int Buffer::bufferLen() {
    return buffer.size();
}

// Métodos para controle do mutex
void Buffer::down() {
    pthread_mutex_trylock(&mutex);
}

void Buffer::up() {
    pthread_mutex_unlock(&mutex);
}

// Métodos para controle do semáforo do produtor
void Buffer::downProdutor() {
    while (bufferLen() == cheio) {
        cout << "\nProdutor Parado" << endl;
        pthread_cond_wait(&condicaoProdutor, &mutex);
    }
}

void Buffer::upProdutor() {
    pthread_cond_signal(&condicaoProdutor);
}

// Métodos para controle do semáforo do consumidor
void Buffer::downConsumidor() {
    while (bufferLen() == 0) {
        cout << "\nConsumidor Parado" << endl;
        pthread_cond_wait(&condicaoConsumidor, &mutex);
    }
}

void Buffer::upConsumidor() {
    pthread_cond_signal(&condicaoConsumidor);
}

// Método do produtor para produzir e inserir um item no buffer
void Buffer::produzir(int item) {
    downProdutor();           // Fica esperando enquanto o buffer não está vazio
    down();                   // Entra na região crítica
    insertItem(item);         // Insere um item no buffer
    up();                     // Sai da região crítica
    upConsumidor();           // Envia um sinal para o consumidor de que há itens no buffer
}

// Método do consumidor para consumir e remover um item do buffer
void Buffer::consumir(int &item) {
    downConsumidor();      // Fica esperando o buffer não estar vazio
    down();                // Entra na região crítica
    item = removeItem();   // Remove um item do buffer
    up();                  // Sai da região crítica
    upProdutor();          // Envia um sinal para o produtor que o buffer não está lotado
}

// Métodos para obter os contadores
int Buffer::getItensProduzidos() {
    return this->produzidos;
}

int Buffer::getItensConsumidos() {
    return this->consumidos;
}

// Classe Consumidor
Consumidor::Consumidor(Buffer *buffer, int qtdItensConsumir, int consumoPorSegundo) {
    this->buffer = buffer;
    this->qtdItensConsumir = qtdItensConsumir;
    this->consumoPorSegundo = consumoPorSegundo;
}

void Consumidor::run() {
    int item;
    int sleepTempo = 1000 / consumoPorSegundo;
    std::cout << "Consumidor em modo Sleep: " << sleepTempo << std::endl;

    for (int i = 0; i < qtdItensConsumir; i++) {
        buffer->consumir(item);
        std::cout << i + 1 << " - Item removido: " << item << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTempo));
    }
}

// Classe Produtor
Produtor::Produtor(Buffer *buffer, int qtdItensProduzir, int itensPorSegundo) {
    this->buffer = buffer;
    this->qtdItensProduzir = qtdItensProduzir;
    this->itensPorSegundo = itensPorSegundo;
    srand(static_cast<unsigned>(time(NULL)));
}

void Produtor::run() {
    int item;

    int sleepTempo = 1000 / itensPorSegundo;
    cout << "Produto em modo sleep: " << sleepTempo << endl;

    for (int i = 0; i < qtdItensProduzir; i++) {
        item = rand();           // Gera um novo item
        buffer->produzir(item);  // Adiciona no buffer
        cout << i + 1 << " - Produzido: " << item << endl;
        this_thread::sleep_for(chrono::milliseconds(sleepTempo));
    }
}
