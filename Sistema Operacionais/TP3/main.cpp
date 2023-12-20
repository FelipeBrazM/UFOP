#include <pthread.h>
#include "buffer.h"

#define NUM_THREADS 2

void *execConsumidor(void *consumidor) {
    Consumidor *myConsumidor = static_cast<Consumidor*>(consumidor);
    myConsumidor->run();
    pthread_exit(NULL);
}

void *execProdutor(void *produtor) {
    Produtor *myProdutor = static_cast<Produtor*>(produtor);
    myProdutor->run();
    pthread_exit(NULL);
}

int leitura(string texto){
    cout << texto;
    int resposta;
    cin >> resposta;
    return resposta;
}

void linhaSeparacao(){
    cout << "===============================================================================\n";
}

int main() {
    
    int tamanhoBuffer = leitura("Digite o tamanho do buffer: ");
    linhaSeparacao();
    int qtdItensProduzir = leitura("Digite quantos itens serão produzidos: ");
    int producaoPorSegundo = leitura("Digite quantos itens serão produzidos por segundo: ");
    linhaSeparacao();
    int qtdItensConsumir = qtdItensProduzir;
    int consumoPorSegundo = leitura("Digite quantos itens serão consumidos por segundo: ");
    linhaSeparacao();

    Buffer buffer(tamanhoBuffer);
    Consumidor consumidor(&buffer, qtdItensConsumir, consumoPorSegundo);
    Produtor produtor(&buffer, qtdItensProduzir, producaoPorSegundo);

    pthread_t threads[NUM_THREADS];

    pthread_create(&threads[1], NULL, execProdutor, static_cast<void*>(&produtor));
    pthread_create(&threads[0], NULL, execConsumidor, static_cast<void*>(&consumidor));

    for(int i = 0; i < NUM_THREADS; i++) pthread_join(threads[i], NULL);
    
    linhaSeparacao();
    cout << "Quantidade de itens produzidos: " << buffer.getItensProduzidos() << endl;
    cout << "Quantidade de itens consumidos: " << buffer.getItensConsumidos() << endl;



    return 0;
}
