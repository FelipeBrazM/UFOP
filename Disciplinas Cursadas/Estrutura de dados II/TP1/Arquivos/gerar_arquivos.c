#include <time.h>
#include "../estruturas.h"

#define TAM_DADO_2 25
#define TAM_DADO_3 100


void vetorInverso(TipoRegistro * arr, int tamanho) {
    int comeco = 0;
    int fim = tamanho - 1;

    while (comeco < fim) {
        // Troca os elementos do comeco com o fim
        TipoRegistro aux = arr[comeco];
        arr[comeco] = arr[fim];
        arr[fim] = aux;

        // Move o indice para o centro
        comeco++;
        fim--;
    }
}

void vetorAleatorio(TipoRegistro arr[], int tamanho) {
    srand(time(NULL));

    for (int i = tamanho - 1; i > 0; i--) {
        // Generate a random index between 0 and i (inclusive)
        int j = rand() % (i + 1);

        // Troca os elementos das posicoes i e j
        TipoRegistro aux = arr[i];
        arr[i] = arr[j];
        arr[j] = aux;
    }
}


int main(){

    srand(time(NULL));

    char * caracteres = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789!@#$&*";
    int tamString = strlen(caracteres);

    int gerar_quantos_tipos = 2;
    //gerar_quantos_tipos   1    2     3      4       5
    int qtdItens[5] =      {100, 1000, 10000, 100000, 1000000};
    char qtdItens_string[5][8] = {"100", "1000", "10000", "100000", "1000000"};

    TipoRegistro * registros = (TipoRegistro *) malloc(1000000 * sizeof(TipoRegistro));

    //Gerando valores aleatorios para os registros
    for(int i = 0; i < 1000000; i++){
        registros[i].Chave = i+1;
        registros[i].dado1 = rand();

        int numero_de_caracteres = (rand() % TAM_DADO_2)+1;
        int caracter_atual;
        int j;

        //Gerando um tamanho de string e valores aleatórios para a string dado2
        for(j = 0; j < numero_de_caracteres; j++){
            caracter_atual = rand() % tamString;
            registros[i].dado2[j] = caracteres[caracter_atual];
        }
        registros[i].dado2[j] = '\0';

        //Gerando um tamanho de string e valores aleatórios para a string dado3
        numero_de_caracteres = (rand() % TAM_DADO_3) + 1;
        for(j = 0; j < numero_de_caracteres; j++){
            caracter_atual = rand() % tamString;
            registros[i].dado3[j] = caracteres[caracter_atual];
        }
        registros[i].dado3[j] = '\0';
    }
    printf("Valores aleatórios gerados.\n");


    //Salvando os dados em ordem crescente
    for(int i = 0; i <=gerar_quantos_tipos; i++){
        char fileName[51];
        strcpy(fileName, qtdItens_string[i]);
        strcat(fileName, "-crescente.bin");
        FILE * arquivo = fopen(fileName,"wb");
        fwrite(registros, sizeof(TipoRegistro), qtdItens[i], arquivo);
        fclose(arquivo);
    }
    printf("Arquivo crescente salvo.\n");


    //Salvando os dados em ordem decrescente
    vetorInverso(registros, 1000000);
    for(int i = 0; i < gerar_quantos_tipos; i++){
        char fileName[51];
        strcpy(fileName, qtdItens_string[i]);
        strcat(fileName, "-decrescente.bin");
        FILE * arquivo = fopen( fileName ,"wb");
        fwrite(registros, sizeof(TipoRegistro), qtdItens[i], arquivo);
        fclose(arquivo);
    }
    printf("Arquivo decrescente salvo.\n");



    //Salvando em ordem aleatório
    vetorAleatorio(registros, 1000000);
    for(int i = 0; i < gerar_quantos_tipos; i++){
        char fileName[51];
        strcpy(fileName, qtdItens_string[i]);
        strcat(fileName, "-aleatorio.bin");
        FILE * arquivo = fopen(fileName ,"wb");
        fwrite(registros, sizeof(TipoRegistro), qtdItens[i], arquivo);
        fclose(arquivo);
    }
    printf("Arquivo aleatório salvo.\n");

    free(registros);

    return 0;
}