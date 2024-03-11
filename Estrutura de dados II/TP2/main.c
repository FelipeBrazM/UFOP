#include "estruturas.h"
#include "area.h"
#include "quickSort.h"
#include "intercalacao.h"

bool verificaInteiro(char * string){
    //Verifica se todos os valores contidos na string sao valores numericos
    int tamString = strlen(string);
    for(int i = 0; i < tamString; i++)
        if(!isdigit(string[i])) return false;
    return true;
}

bool verificaInputs(int argc, char const *argv[], InfoOrdenacao * infoOrdenacao){
    
    //Verificando o tamanho da entrada
    if(argc < 4 || argc > 5){ 
        printf("Os dados devem ser passados no terminal por: \n\t./executavel <metodo> <quantidade> <situação> [-P]\n");
        return false;
    }

    bool dadosCorretos = true;

    char tempString[50];
    strcpy(tempString, argv[1]);

    //Verificando se os dados sao inteiros e se podem ser convertidos
    if(!verificaInteiro(tempString) || atoi(argv[1]) <= 0 || atoi(argv[1]) >= 4){
        printf("O método deve ser passado como um inteiro.\n");
        printf("O método deve estar no intervalo [1, 3].\n");
        printf("\t1 - Intercalação balanceada por vários caminhos com método de ordenação interna de ED1\n");
        printf("\t2 - Intercalação balanceada por vários caminhos com seleção por substituição\n");
        printf("\t3 - QuickSort externo\n");
        dadosCorretos = false;
    }
    else{
        infoOrdenacao->metodo = atoi(argv[1]);
    }

    //Verificado se o numero de itens para ordenar esta correto
    int qtd;
    strcpy(tempString, argv[2]);
    if(!verificaInteiro(tempString) || atoi(argv[2]) < 0 || atoi(argv[2]) > 471705){
        printf("O número de itens a ser ordenado deve ser igual a 100, 1.000, 10.000, 100.000 ou 471.705\n");
        dadosCorretos = false;
    }
    else{
        qtd = atoi(argv[2]);

        if(qtd != 100 && qtd != 1000 && qtd != 10000 && qtd != 100000 && qtd != 471705){
            printf("O número de itens a ser ordenado deve ser igual a 100, 1.000, 10.000, 100.000 ou 471.705\n");
            dadosCorretos = false;
        }
        else infoOrdenacao->quantidade = qtd;
    }

    //Verifica se o tipo de ordenação esta correto
    strcpy(tempString, argv[3]);
    if(!verificaInteiro(tempString) || atoi(argv[3]) <= 0 || atoi(argv[3]) >= 4){
        printf("A situação deve ser passado como um inteiro que está no intervalo [1, 3].\n");
        printf("\t1 - Arquivo ordenado ascendentemente pelas notas\n");
        printf("\t2 - Arquivo ordenado descendentemente pelas notas\n");
        printf("\t3 - Arquivo desordenado aleatoriamente pelas notas\n");
        dadosCorretos = false;
    }
    else infoOrdenacao->situacao = atoi(argv[3]);

    if(argc == 5){
        if(strcmp(argv[4], "-p") == 0 || strcmp(argv[4], "-P") == 0) 
            infoOrdenacao->p = true;
        else 
            infoOrdenacao->p = false;
    }
    else infoOrdenacao->p = false;
    

    return dadosCorretos;
}

void gerarArquivoCopia(InfoOrdenacao * infoOrdenacao) {
    FILE * arq;
    char ordenacao[20];
    if(infoOrdenacao->situacao == ASCENDENTE){ 
        arq = fopen("PROVAO_CRESCENTE.bin", "rb");
        strcpy(ordenacao, "crescente");
    }
    else if(infoOrdenacao->situacao == DESCENDENTE){ 
        arq = fopen("PROVAO_DECRESCENTE.bin", "rb");
        strcpy(ordenacao, "decrescente");
    }
    else{ 
        arq = fopen("PROVAO_ALEATORIO.bin", "rb");
        strcpy(ordenacao, "aleatorio");
    }

    char metodo[20];
    if(infoOrdenacao->metodo == BALANCEADA_BLOCO_OI) strcpy(metodo, "Bloco_ord_interna");
    else if(infoOrdenacao->metodo == BALANCEADA_HEAP) strcpy(metodo, "Bloco_heap");
    else strcpy(metodo, "QuickSort");

    //Lendo os n primeiros dados do arquivo de origem
    TipoRegistro * registros = malloc(infoOrdenacao->quantidade * sizeof(TipoRegistro));
    fread(registros, sizeof(TipoRegistro), infoOrdenacao->quantidade, arq);
    infoOrdenacao->acessos.qtdLeitura += 1;

    //Gerando o nome do arquivo de destino
    char arquivoDestino[50];
    sprintf(arquivoDestino, "%s-%s-%d.bin", metodo, ordenacao, infoOrdenacao->quantidade);
    strcpy(infoOrdenacao->nomeArquivo, arquivoDestino);

    //Escrevendo os n primeiros dados no arquivo de destino
    FILE * novoArq = fopen(arquivoDestino, "wb+");
    fwrite(registros, sizeof(TipoRegistro), infoOrdenacao->quantidade, novoArq);
    infoOrdenacao->acessos.qtdEscrita += 1;

    fclose(arq);
    fclose(novoArq);
    free(registros);
}

void binarioParaTXT_printarDados(InfoOrdenacao * infoOrdenacao){

    FILE * arqOrigem = fopen(infoOrdenacao->nomeArquivo, "rb");

    //Criando e abrindo o arquivo de saida
    char nomeArqDestino[100];
    strcpy(nomeArqDestino, infoOrdenacao->nomeArquivo);
    int tamNomeArquivo = strlen(nomeArqDestino);
    nomeArqDestino[tamNomeArquivo-1] = 't';
    nomeArqDestino[tamNomeArquivo-2] = 'x';
    nomeArqDestino[tamNomeArquivo-3] = 't';

    FILE * arqDestino = fopen(nomeArqDestino, "w");

    //Lendo os dados do binario e escrevendo no txt
    TipoRegistro buffer[20];
    size_t itensLidos;

    if(!infoOrdenacao->p){
        while ((itensLidos = fread(buffer, sizeof(TipoRegistro), 20, arqOrigem)) > 0) {
            infoOrdenacao->acessos.qtdLeituraBinTxt += 1;
            for(int i = 0; i < itensLidos; i++){
                fprintf(arqDestino,"%-8d %-5.2f %-2s %-50s %-30s\n", buffer[i].Chave, buffer[i].nota, buffer[i].estado, buffer[i].cidade, buffer[i].curso);
                infoOrdenacao->acessos.qtdEscritaBinTxt += 1;
            }
        }
    }
    else{
        printf("\n");
        while ((itensLidos = fread(buffer, sizeof(TipoRegistro), 20, arqOrigem)) > 0) {
            infoOrdenacao->acessos.qtdLeituraBinTxt += 1;
            for(int i = 0; i < itensLidos; i++){
                printf("%-8d %-5.2f %-2s %-50s %-30s\n", buffer[i].Chave, buffer[i].nota, buffer[i].estado, buffer[i].cidade, buffer[i].curso);
                fprintf(arqDestino,"%-8d %-5.2f %-2s %-50s %-30s\n", buffer[i].Chave, buffer[i].nota, buffer[i].estado, buffer[i].cidade, buffer[i].curso);
                infoOrdenacao->acessos.qtdEscritaBinTxt += 1;
            }
        }
        printf("\n");
    }
    
    fclose(arqDestino);
    fclose(arqOrigem);

}

InfoOrdenacao inicializaInfoOrdenacao(){
    InfoOrdenacao infoOrdenacao;

    infoOrdenacao.acessos.qtdEscrita = 0;
    infoOrdenacao.acessos.qtdEscritaGeracaoBlocos = 0;
    infoOrdenacao.acessos.qtdLeitura = 0;
    infoOrdenacao.acessos.qtdLeituraGeracaoBlocos = 0;
    infoOrdenacao.acessos.qtdLeituraBinTxt = 0;
    infoOrdenacao.acessos.qtdEscritaBinTxt = 0;

    infoOrdenacao.acessos.comparacoesChave = 0;

    infoOrdenacao.acessos.horarioInicio = clock();

    return infoOrdenacao;
}

void exibirInformacoesOrdenacao(InfoOrdenacao infoOrdernacao){
    printf("Quantidade de leitura:                                    %7d\n", infoOrdernacao.acessos.qtdLeitura);
    if(infoOrdernacao.metodo != QUICKSORT) printf("Quantidade de leitura na geração de blocos:               %7d\n", infoOrdernacao.acessos.qtdLeituraGeracaoBlocos);
    printf("Quantidade de leitura na transformação de .bin para .txt: %7d\n", infoOrdernacao.acessos.qtdLeituraBinTxt);
    int qtdLeituraTotal = infoOrdernacao.acessos.qtdLeitura + infoOrdernacao.acessos.qtdLeituraGeracaoBlocos + infoOrdernacao.acessos.qtdLeituraBinTxt;
    printf("Quantidade de leituras totais:                            %7d\n\n", qtdLeituraTotal);


    printf("Quantidade de escrita:                                    %7d\n", infoOrdernacao.acessos.qtdEscrita);
    if(infoOrdernacao.metodo != QUICKSORT) printf("Quantidade de escrita na geração de blocos:               %7d\n", infoOrdernacao.acessos.qtdEscritaGeracaoBlocos);
    printf("Quantidade de escrita na transformação de .bin para .txt: %7d\n", infoOrdernacao.acessos.qtdEscritaBinTxt);
    int qtdEscritaTotal = infoOrdernacao.acessos.qtdEscrita + infoOrdernacao.acessos.qtdEscritaGeracaoBlocos + infoOrdernacao.acessos.qtdEscritaBinTxt;
    printf("Quantidade de escritas totais:                            %7d\n\n", qtdEscritaTotal);

    printf("Quantidade de comparações entre notas: %d\n", infoOrdernacao.acessos.comparacoesChave);

    double tempoExecucao = ((double) (infoOrdernacao.acessos.horarioFim - infoOrdernacao.acessos.horarioInicio)) / CLOCKS_PER_SEC;

    printf("Tempo de execução: %lfs.\n", tempoExecucao);

}

int main(int argc, char const *argv[]){
    InfoOrdenacao infoOrdenacao = inicializaInfoOrdenacao();
    
    //Verificado se os dados passados no terminal estao corretos
    if(!verificaInputs(argc, argv, &infoOrdenacao)) return 0;

    gerarArquivoCopia(&infoOrdenacao);

    //Selecionando o metodo de ordenacao
    if(infoOrdenacao.metodo == QUICKSORT) quickSort(&infoOrdenacao);
    else intercalacao_balanceada(&infoOrdenacao);

    //Transformando os dados do arquivo binario para o txt
    binarioParaTXT_printarDados(&infoOrdenacao);

    //Finalizando a contagem de tempo do programa
    infoOrdenacao.acessos.horarioFim = clock();

    //Printa os dados da ordenacao
    exibirInformacoesOrdenacao(infoOrdenacao);

    return 0;
}