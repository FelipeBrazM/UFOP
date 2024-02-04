#include <pthread.h>
#include "buffer.h"

#define NUM_THREADS 2

void *runConsumidor(void *consumidor) {
    Consumidor *myConsumidor = static_cast<Consumidor*>(consumidor);
    myConsumidor->run();
    pthread_exit(NULL);
}

void *runProdutor(void *produtor) {
    Produtor *myProdutor = static_cast<Produtor*>(produtor);
    myProdutor->run();
    pthread_exit(NULL);
}

int read(string text){
    cout << text;
    int retorno;
    cin >> retorno;
    return retorno;
}

void QuebraLinha(){
    cout << "\x1b[36m""-------------------------------------------------------------------------------\n""\x1b[0m";
}

int main() {
    
    int tamanhoBuffer = read("\x1b[33m""Entre com o tamanho do Buffer: ""\x1b[0m");
    QuebraLinha();
    int qtdItensProduzir = read("\x1b[33m""Quantos itens serão produzidos? ""\x1b[0m");
    int producaoPorSegundo = read("\x1b[33m""Por segundo serão produzidos quantos itens? ""\x1b[0m");
    QuebraLinha();
    int qtdItensConsumir = qtdItensProduzir;
    int consumoPorSegundo = read("\x1b[33m""Por segundo serão consumidos quantos itens? ""\x1b[0m");
    QuebraLinha();

    Buffer buffer(tamanhoBuffer);
    Consumidor consumidor(&buffer, qtdItensConsumir, consumoPorSegundo);
    Produtor produtor(&buffer, qtdItensProduzir, producaoPorSegundo);

    pthread_t threads[NUM_THREADS];

    pthread_create(&threads[1], NULL, runProdutor, static_cast<void*>(&produtor));
    pthread_create(&threads[0], NULL, runConsumidor, static_cast<void*>(&consumidor));

    for(int i = 0; i < NUM_THREADS; i++) pthread_join(threads[i], NULL);
    
    QuebraLinha();
    cout << "\x1b[33m""Total de itens produzidos: ""\x1b[0m" << buffer.getItensProduzidos() << endl;
    cout << "\x1b[33m""Total de itens consumidos: ""\x1b[0m" << buffer.getItensConsumidos() << endl;



    return 0;
}
