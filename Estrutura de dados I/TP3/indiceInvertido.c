#include "indiceInvertido.h"

/**
 * @brief Inicia o vetor de IndiceInvertido com todas as chaves vazias
 * 
 * @param IndiceIvertido 
 * @return void
*/
void inicia(IndiceInvertido indiceInvertido){
    int i;

    for (i = 0; i < M ; i ++) {
        //memcpy(indiceInvertido[i].chave, VAZIO, N);
        strcpy(indiceInvertido[i].chave, VAZIO);
        indiceInvertido[i].n = 0;
    }
}

/**
 * @brief Insere um documento e as suas palavras chave no vetor de itens
 * 
 * @param indiceInvertido vetor de itens
 * @param chave chave do documento
 * @param documento nome do documento a ser inserido
 * 
 * @return bool
*/
#ifdef ANALISE_RELATORIO
bool insereDocumento(IndiceInvertido indiceInvertido, Chave chave, NomeDocumento documento, int *qtdColisoes)
#else
bool insereDocumento(IndiceInvertido indiceInvertido, Chave chave, NomeDocumento documento)
#endif
{
    int indexBusca = busca(indiceInvertido, chave); 
    //caso a palavra (chave) ja exista no indice invertido, sera adicionado o nome do documento naquele item relacionado a essa chave
    if (indexBusca >= 0){
        strcpy(indiceInvertido[indexBusca].documentos[indiceInvertido[indexBusca].n], documento);
        indiceInvertido[indexBusca].n++;
        return true;
    }

    int j = 0;
    int ini = h (chave , M);

    while ( strcmp (indiceInvertido[( ini + j) % M ].chave , VAZIO) != 0 && j < M ) {
        j ++; 
        #ifdef ANALISE_RELATORIO
            (*qtdColisoes)++;
        #endif
    }
    if (j < M){
        //como nao existe a palavra no indice invertido, sera adicionado na posicao (ini+j)%M a palavra(chave) e o nome do documento referente
        strcpy(indiceInvertido[(ini + j) % M].chave, chave);
        strcpy(indiceInvertido[(ini + j) % M].documentos[indiceInvertido[(ini + j) % M].n], documento);
        indiceInvertido[(ini + j) % M].n++;
        return true;
    }
    return false;
}

/**
 * @brief Pesquisa o index de uma chave especificada
 * 
 * @param indiceInvertido onde os dados estao salvos
 * @param chave qual a chave que sera procurada 
 * 
*/
int busca(IndiceInvertido indiceInvertido, Chave chave){
    int j = 0;
    int ini = h(chave, M);
    while(strcmp(indiceInvertido[( ini + j) % M ].chave , VAZIO) != 0 && 
          strcmp (indiceInvertido[( ini + j ) % M ].chave , chave) != 0 &&
          j < M ){
        j++;
    }

    if(strcmp(indiceInvertido[(ini + j) % M].chave, chave) == 0){
        return (ini + j) % M;
    }
    return -1;
}

/**
 * @brief Remove documento do vetor de documentos que serao impressos apos a busca de palavras(chaves)
 * 
 * @param documentos Vetor de documentos que sera modificado
 * @param contDocumentos Quantidade de documentos que existem no total
 * @param posicaoRemover Qual a posicao que tera o item que sera removido
 * 
*/
void removeDocumento(NomeDocumento * documentos, int * contDocumentos, int posicaoRemover){
    for(int i = posicaoRemover + 1; i < *contDocumentos; i++){
        strcpy(documentos[i-1], documentos[i]);
    }
    (*contDocumentos)--;
}

/**
 * @brief Procura todas os documentos que possuem as palavras chaves indicadas
 * 
 * @param indiceInvertido 
 * @param chave Todas as chaves que serão utilizadas para pesquisar
 * @param n Número de chaves que serão utilizadas
 * @param documento documentos que possuem as palavras chaves
 * @param contDocumentos quantidade de documentos com as palavras chaves
 * 
*/
int consulta(IndiceInvertido indiceInvertido, Chave *chave, int n, NomeDocumento* documento, int *contDocumentos){
    int *indicesChaves = (int *) malloc(n * sizeof(int));
    
    #ifdef ANALISE_RELATORIO
        memoriaGasta(n*sizeof(int), false);
    #endif

    for(int i = 0; i < n; i++){
        indicesChaves[i] = busca(indiceInvertido, chave[i]);
        if(indicesChaves[i] == -1){
            free(indicesChaves);
            return 0;
        }
    }

    //copiando o nome dos documentos que possuem a primeira palavra(chave) buscada
    *contDocumentos = indiceInvertido[indicesChaves[0]].n;
    for(int i=0; i < *contDocumentos; i++){
        strcpy(documento[i], indiceInvertido[indicesChaves[0]].documentos[i]);
    }

    //verificando se os documentos que possuem a primeira palavra(chave), possuem as proximas palavras tambem
    //caso nao possuam, removo ela do vetor de documentos que serao impressos
    bool removerDoc;
    for(int i=1; i < n; i++){ //Passando por todas as palavras(chaves) buscadas
        for(int j=0; j < *contDocumentos; j++){ // Passa pelos documentos do vetor de documentos que serao impressos
            removerDoc = true;

            for(int k=0; k < indiceInvertido[indicesChaves[i]].n; k++){ //Passa por todos os nomes de documentos que possuem x palavra(chave)
                if(strcmp(documento[j], indiceInvertido[indicesChaves[i]].documentos[k]) == 0){
                    removerDoc = false;
                    break;
                }
            }
               
            if(removerDoc){
                removeDocumento(documento, contDocumentos, j);
                j--;
            }
        }
    }
    free(indicesChaves);
    return *contDocumentos > 0 ? 1 : 0;
}

/**
 * @brief Imprime o indice invertido
 * 
 * @param indiceInvertido onde os dados estao salvos
 * 
*/
void imprimeIndiceInvertido(IndiceInvertido indiceInvertido){
    for(int i=0; i < M; i++){
        if(strcmp(indiceInvertido[i].chave, VAZIO) != 0){
            printf("%s -", indiceInvertido[i].chave);

            for (int j = 0; j < indiceInvertido[i].n; j++)
                printf(" %s", indiceInvertido[i].documentos[j]);

            printf("\n");
        }
    }
}

/**
 * @brief imprime documentos que contem as palavras buscadas
 * 
 * @param documentos documentos que possuem as palavras chaves
 * @param n quantidade de documentos para serem exibidos
 * 
*/
void imprimeDocumentos(NomeDocumento *documentos, int n){
    for(int i=0; i<n; i++)
        printf("%s\n", documentos[i]);
}

/**
 * @brief Le as entradas do usuario e salva todos os documentos e chaves no indice invertido
 * 
 * @param indiceInvertido vetor onde os dados serao salvos
 * @param nDocumentos numero de documentos 
 * 
*/
#ifdef ANALISE_RELATORIO
void leEntrada(IndiceInvertido indiceInvertido, int * nDocumentos, int *qtdColisoes)
#else
void leEntrada(IndiceInvertido indiceInvertido, int * nDocumentos)
#endif
{
    scanf("%d", nDocumentos);
    getchar();

    int tamMax = (N * NN) + D; //tamanho maximo de caracteres de cada linha da entrada

    char documentoChaves[tamMax]; // armazena a entrada com documento e suas palavras-chaves

    #ifdef ANALISE_RELATORIO
        memoriaGasta(tamMax * sizeof(char), false);
    #endif

    for(int i = 0; i < *nDocumentos; i++){
        fgets(documentoChaves, tamMax, stdin);
    
        documentoChaves[strcspn(documentoChaves, "\n")] = '\0';

        char * token = strtok(documentoChaves, " ");
        char nomeDocumento [D];
        strcpy(nomeDocumento, token);

        token = strtok(NULL, " ");
        while(token != NULL){

            #ifdef ANALISE_RELATORIO
                insereDocumento(indiceInvertido, token, nomeDocumento, qtdColisoes);
            #else
                insereDocumento(indiceInvertido, token, nomeDocumento);
            #endif

            token = strtok(NULL, " ");
        }
    }
}

/**
 * @brief Verifica se o usuario ira imprimir ou buscar
 * 
 * @param indiceInvertido vetor onde os dados estao salvos
 * @param nDocumentos numero de documentos 
 * 
*/
void leOpcao(IndiceInvertido indiceInvertido, int nDocumentos){
    char opcao;
    scanf("%c", &opcao);

    if(opcao == 'I')
        imprimeIndiceInvertido(indiceInvertido);
        
    else{ // opcao == 'B' - busca palavras no indiceInvertido
        char palavrasBuscadas[N*100 + 102]; //Sao ate 100 palavras, cada uma delas com 21 caracteres, e +102 e por causa dos 100 espacos entre as palavras, \n e \0
        fgets(palavrasBuscadas, N*100 + 102, stdin);
        palavrasBuscadas[strcspn(palavrasBuscadas, "\n")] = '\0';

        executaBuscaDoUsuario(indiceInvertido, nDocumentos, palavrasBuscadas);
    }
}

/**
 * @brief Executa a busca dos arquivos que possuem todas as palavras chave
 * 
 * @param indiceInvertido vetor onde os dados estao salvos
 * @param nDocumentos numero de documentos 
 * @param palavrasBuscadas vetor com todas as palavras a serem buscadas
 * 
*/
void executaBuscaDoUsuario(IndiceInvertido indiceInvertido, int nDocumentos, char *palavrasBuscadas){
    //Salvando todas as palavras de pesquisa em um vetor
    Chave palavrasChave[100];
    int qtdPalavrasChave = 0;

    copiaPalavrasBuscadas(palavrasChave, &qtdPalavrasChave, palavrasBuscadas);

    NomeDocumento *documentos = (NomeDocumento *) malloc(nDocumentos * sizeof(NomeDocumento));
    
    #ifdef ANALISE_RELATORIO
        memoriaGasta(100 * sizeof(Chave), false);
        memoriaGasta(nDocumentos * sizeof(NomeDocumento), false);
    #endif

    int contDocumentos;

    if(consulta(indiceInvertido, palavrasChave, qtdPalavrasChave, documentos, &contDocumentos)){
        sort(documentos, contDocumentos);

        imprimeDocumentos(documentos, contDocumentos);
    }
    else
        printf("none\n");

    free(documentos);
}

/**
 * @brief Salvando todas as palavras de pesquisa em um vetor do tipo Chave
 * 
 * @param indiceInvertido vetor onde os dados estao salvos
 * @param nDocumentos numero de documentos 
 * @param palavrasBuscadas vetor com todas as palavras a serem buscadas
 * 
*/
void copiaPalavrasBuscadas(Chave *palavrasChave, int *qtdPalavrasChave, char *palavrasBuscadas){
    char * token = strtok(palavrasBuscadas, " ");

    while(token != NULL){
        strcpy(palavrasChave[*qtdPalavrasChave], token);

        (*qtdPalavrasChave)++;

        token = strtok(NULL, " ");
    }
}

/**
 * @brief Chama a funcao de ordenacao correta
 * 
 * @param documento todos os documentos a serem ordenados
 * @param n numero de documentos 
 * 
*/
void sort(NomeDocumento* documento, int n){
    mergeSort(documento, 0, n-1);
}

/**
 * @brief Merge Sort para ordenar
*/
void merge(NomeDocumento *documentos, int l, int m, int r){
    int size_l = (m-l+1);
    int size_r = (r-m);

    NomeDocumento *vet_l = malloc(size_l * sizeof(NomeDocumento));
    NomeDocumento *vet_r = malloc(size_r * sizeof(NomeDocumento));

    #ifdef ANALISE_RELATORIO
        memoriaGasta(size_l * sizeof(NomeDocumento), false);
        memoriaGasta(size_r * sizeof(NomeDocumento), false);
    #endif

    int i, j;

    for (i = 0; i < size_l; i++)
        strcpy(vet_l[i], documentos[i + l]);

    for(j = 0; j < size_r; j++)
        strcpy(vet_r[j], documentos[m + j + 1]);
    
    i = 0;
    j = 0;

    for (int k = l; k <= r; k++){
        if(i == size_l)
            strcpy(documentos[k], vet_r[j++]);

        else if(j == size_r)
            strcpy(documentos[k], vet_l[i++]);

        else if(strcmp(vet_l[i], vet_r[j]) <= 0)
            strcpy(documentos[k], vet_l[i++]);

        else
            strcpy(documentos[k], vet_r[j++]);
    }
    
    free(vet_l);
    free(vet_r);
}

void mergeSort(NomeDocumento *documentos, int l, int r){
    int m;
    
    if(l<r){
        m = (l+r) / 2;
        mergeSort(documentos, l, m);
        mergeSort(documentos, m+1, r);
        merge(documentos, l, m, r);
    }
}

void printColisoes(int qtdColisoes){
    printf("Quantidade de colisões: %d\n", qtdColisoes);
}


void memoriaGasta(long int memoria, bool exibir){
    static long int totalMemoria = 0;
    totalMemoria += memoria;

    if(exibir){
        printf("Total de memória: %ld bytes\n", totalMemoria);
    }
}