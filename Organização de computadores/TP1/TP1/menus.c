#include "menus.h"

//Verifica se todas as entradas sao validas, se estao nos intervalos determinados e se o metodo pode utilizar determinada ordenacao de arquivo
bool verificaInputsValidos(int metodo, int quantidade, int situacao){
    bool dadosValidos = true;

    //Verifica se o metodo escolheu e valido
    if(metodo > 4 || metodo < 1){
        printErr("O método deve estar entre 1 e 4.\n");
        printf("\t1 - Acesso sequencial indexado;\n");
        printf("\t2 - Árvore binária de pesquisa;\n");
        printf("\t3 - Árvore B;\n");
        printf("\t4 - Árvore B*\n");

        dadosValidos = false;
    }

    //Verifica se a quantidade de itens nos arquivos sao validas
    if(quantidade != 100 && quantidade != 1000 && quantidade != 10000 && quantidade != 100000 && quantidade != 1000000) {
        printErr(("Quantidade de dados inválidas.\n"));
        printf("\tAs quantidades podem ser: 100, 1000, 10000, 100000 ou 1000000\n");
        dadosValidos = false;
    }

    //Verifica se a ordenacao do arquivo e valida
    if(situacao > 3 || situacao < 1){
        printErr("A situação deve estar entre 1 e 3.\n");
        printf("\t1 - Crescente;\n");
        printf("\t2 - Decrescente;\n");
        printf("\t3 - Aleatório\n");

        dadosValidos = false;
    }
    
    //Verifica se esta utilizando o acesso sequencial indexado com dados aleatorios
    if(metodo == 1 && situacao > 1){
        printWarning("O método de acesso sequencial indexado não pode utilizar dados aleatórios nem decrescente.\n");
        dadosValidos = false;
    }

    return dadosValidos;
}

//Retorna uma string com a ordenacao do arquivo
char * verificaSituacao(int situacao){
    if(situacao == 1) return "-crescente.bin";
    else if (situacao == 2) return "-decrescente.bin";
    else return "-aleatorio.bin";
}

//A partir do metodo e ordenacao do arquivo escolhido pelo usuario, gera o nome a ser utilizado na abertura do arquivo
char * geraNomeArquivo(char * quantidade, int situacao, char * nomeArquivo){
    strcpy(nomeArquivo, "Arquivos/");
    char * nome = strcat(quantidade, verificaSituacao(situacao));

    return strcat(nomeArquivo, nome);
}

//Converte uma chave de String para um valor Long
long converteChave(char * chaveStr){
    char * resto;
    int base = 10;
    long chave = strtol(chaveStr, &resto, base);
    
    return chave;
}

//Executa o metodo especificado pelo usuario
int selecionaMetodo(int metodo, long chave, char * nomeArquivo, int quantidade, Resultados * resultado){

    if(metodo == 1)
        return acessoIndexado(nomeArquivo, resultado);

    else if(metodo == 2)
        return arvore_binaria_de_pesquisa(nomeArquivo, resultado);

     else if(metodo == 3)
         return arvore_b(nomeArquivo, quantidade, resultado);
        
    else
        return arvore_b_estrela(chave, nomeArquivo, quantidade, resultado);
   
    return 0;
}

//Imprime todos os resultados que foram obtidos a partir da pesquisa realizada
void imprimeResultados(Resultados * resultado){
    if(resultado->resultadoPesquisa){
        printSuccess("Resultado encontrado\n");

        if(resultado->metodo != 4){
            printf("\tchave: %ld \n\tdado 1: %ld \n\tdado 2: %s \n\tdados 3: %s\n",
            resultado->pesquisar.Chave, resultado->pesquisar.dado1, resultado->pesquisar.dado2, resultado->pesquisar.dado3);
        }
            
        else {
            printf("\tchave: %ld \n\tdado 1: %ld \n\tdado 2: %s \n\tdados 3: %s\n", 
            resultado->pesquisarEstrela.Chave, resultado->pesquisarEstrela.dado1, resultado->pesquisarEstrela.dado2, resultado->pesquisarEstrela.dado3);
        }

        if(resultado->metodo != 4){
            printf("\tchave: %ld \n",
            resultado->pesquisar.Chave);
        }
            
        else {
            printf("\tchave: %ld \n", 
            resultado->pesquisarEstrela.Chave);
        }
    }
    else 
        printErr("Resultado não encontrado para a Chave\n");


    printf("===============\n");
    double tempoPreProcessamento = ((double)(resultado->tempoPreProcessamento[1] - resultado->tempoPreProcessamento[0]))/CLOCKS_PER_SEC;
    double tempoPesquisa = ((double)(resultado->tempoPesquisa[1] - resultado->tempoPesquisa[0]))/CLOCKS_PER_SEC;
    double tempoTotal = tempoPreProcessamento + tempoPesquisa; 

    resultado->tempoPesquisaCalculado = tempoPesquisa;
    resultado->tempoPreProcessamentCalculado = tempoPreProcessamento;
    resultado->tempoTotalCalculado = tempoTotal;

    printf("\tTempo de pré-processamento: %lf s\n", tempoPreProcessamento);
    printf("\tTempo de pesquisa: %.5lf s\n", tempoPesquisa);
    printf("\tTempo total: %.5lf s\n", tempoTotal);
    
    
    long int qtdTransferenciasPreProcessamento = resultado->preProcessamento.transferencias;
    long int qtdComparacoesPreProcessamento = resultado->preProcessamento.comparacoes;
    printf("===============\n");
    printf("\tNúmero de transferências do pré-processamento: %ld\n", qtdTransferenciasPreProcessamento);
    printf("\tNúmero de comparações do pré-processamento: %ld\n", qtdComparacoesPreProcessamento);

    long int qtdTransferenciasPesquisa = resultado->pesquisa.transferencias;
    long int qtdComparacoesPesquisa = resultado->pesquisa.comparacoes;
    printf("===============\n");
    printf("\tNúmero de transferências da pesquisa: %ld\n", qtdTransferenciasPesquisa);
    printf("\tNúmero de comparações da pesquisa: %ld\n", qtdComparacoesPesquisa);

    long int transferenciaTotal = qtdTransferenciasPesquisa + qtdTransferenciasPreProcessamento;
    long int comparacoesTotal = qtdComparacoesPesquisa + qtdComparacoesPreProcessamento;
    printf("===============\n");
    printf("\tNúmero de transferências total: %ld\n", transferenciaTotal);
    printf("\tNúmero de comparações total: %ld\n", comparacoesTotal);

}

//Verifica se ha uma chave repetida dentro de um vetor
bool verificaChaveRepetida(int posicao, int *posicoes, int tam){
    for (int i = 0; i < tam; i++)
        if(posicao == posicoes[i])
            return true;

    return false;
}

//Gera 10 numeros aleatorios para realizar a pesquisa automatizada
bool gerarNumerosAleatorios(char * nomeArquivo, int quantidade, Resultados * resultados){

    int posicao[10];
    TipoRegistro reg;

    FILE * arq = fopen(nomeArquivo, "rb");

    if(arq == NULL) return false;

    int n = 0;
    //Gera as 10 chaves aleatorias para pesquisar
    for(int i = 0; i < 10; i++){

        int posRand = rand()%quantidade;

        if(verificaChaveRepetida(posRand, posicao, n)){
            while(verificaChaveRepetida(posRand, posicao, n)){
                posRand = rand()%quantidade;  
            }
        }
        posicao[i] = posRand;
        n++;
        
        //Lendo a chave e salvando no vetorde resultados
        fseek(arq, (posicao[i])*sizeof(TipoRegistro),SEEK_SET);
        fread(&reg, sizeof(TipoRegistro), 1, arq);
        resultados[i].pesquisar.Chave = reg.Chave;
        resultados[i].pesquisarEstrela.Chave = reg.Chave;

    }

    fclose(arq);
    return true;
}

//Recebe um registro que salvara os resultados e realiza as pesquisas
void realizarPesquisa(Resultados * resultado, long chave, char * nomeArquivo, int quantidade){

    resultado->pesquisar.Chave = chave;
    resultado->pesquisarEstrela.Chave = chave;

    resultado->resultadoPesquisa = selecionaMetodo(resultado->metodo, chave, nomeArquivo, quantidade, resultado);

    imprimeResultados(resultado);

}

void calculaMediaExecucoes(Resultados *resultados){

    double tempoMedioPreProcessamento = 0.0;
    double tempoMedioPesquisa = 0.0;
    double tempoMedioTotal = 0.0;

    int transferenciasMediaPreProcessamento = 0;
    int transferenciasMediaPesquisa = 0;
    int transferenciasMediaTotal = 0;

    int comparacoesMediaPreProcessamento = 0;
    int comparacoesMediaPesquisa = 0;
    int comparacoesMediaTotal = 0;

    for(int i = 0; i < 10; i++){
        tempoMedioPreProcessamento += resultados[i].tempoPreProcessamentCalculado;
        tempoMedioPesquisa += resultados[i].tempoPesquisaCalculado;
        
        transferenciasMediaPreProcessamento += resultados[i].preProcessamento.transferencias;
        transferenciasMediaPesquisa += resultados[i].pesquisa.transferencias;

        comparacoesMediaPreProcessamento += resultados[i].preProcessamento.comparacoes;
        comparacoesMediaPesquisa += resultados[i].pesquisa.comparacoes;
    }   

    tempoMedioPreProcessamento /= 10.0;
    tempoMedioPesquisa /= 10.0;
    tempoMedioTotal += tempoMedioPreProcessamento + tempoMedioPesquisa;

    transferenciasMediaPreProcessamento /= 10.0;
    transferenciasMediaPesquisa /= 10.0;
    transferenciasMediaTotal = transferenciasMediaPreProcessamento + transferenciasMediaPesquisa;

    comparacoesMediaPreProcessamento /= 10.0;
    comparacoesMediaPesquisa /= 10.0;
    comparacoesMediaTotal += comparacoesMediaPreProcessamento + comparacoesMediaPesquisa;


    printf("\n\n");
    /*Tempo médio Pré-processamento*/ printf("Tempo médio de Pré-Processamento: %lfs\n", tempoMedioPreProcessamento);
    /*Tempo médio Pesquisa:*/ printf("Tempo médio de pesquisa: %lfs\n", tempoMedioPesquisa);
    /*Tempo médio total*/ printf("Tempo Médio Total: %lfs\n", tempoMedioTotal);
    /*Transferências média Pré-processamento:*/ printf("Transferências média no pré-processamento: %d\n", transferenciasMediaPreProcessamento);
    /*Transferências média Pesquisa:*/ printf("Transferências média de pesquisa: %d\n", transferenciasMediaPesquisa);
    /*Transferências média total*/ printf("Transferências médias Total: %d\n", transferenciasMediaTotal);
    /*Comparações média Pré-processamento:*/ printf("Comparações média de Pré-Processamento: %d\n", comparacoesMediaPreProcessamento);
    /*Comparações média Pesquisa:*/ printf("Comparações média de pesquisa: %d\n", comparacoesMediaPesquisa);
    /*Comparações média Total*/ printf("Comparações média total: %d\n", comparacoesMediaTotal);

}

void imprimirChavesArquivo(char *nomeArquivo, int quantidade){
    FILE *arq;
    if((arq = fopen(nomeArquivo, "rb")) == NULL)
    {
        printf("Erro na abertura do arquivo\n"); 
        return;
    }
    
    TipoRegistro *registros = (TipoRegistro*) (quantidade * sizeof(TipoRegistro));
    fread(registros, sizeof(TipoRegistro), quantidade, arq);
    printf("\tCHAVES PRESENTES NO ARQUIVO:\n");
    for (int i = 0; i < quantidade; i++)
    {
        printf("Chave: %ld\n", registros[i].Chave);
    }
    free(registros);
    fclose(arq);
}