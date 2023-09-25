#include "indiceInvertido.h"

/**
 * @brief Inicia a tabela hash do tipo IndiceInvertido
 * 
 * @param indiceIvertido 
 * @return void
*/
void inicia(IndiceInvertido *indiceInvertido){
    int i;

    for (i = 0; i < M ; i ++) {
        indiceInvertido->listas[i].pCabeca = (Celula *) malloc(sizeof(Celula));
        indiceInvertido->listas[i].pCabeca->pProx = NULL;     
        indiceInvertido->listas[i].pUltimo = indiceInvertido->listas[i].pCabeca;
    }
}

/**
 * @brief Insere um documento e as suas palavras chave no vetor de listas do IndiceInvertido
 * 
 * @param indiceInvertido vetor de itens
 * @param chave chave do documento
 * @param documento nome do documento a ser inserido
 * 
 * @return bool
*/

bool insereDocumento(IndiceInvertido *indiceInvertido, Chave chave, NomeDocumento documento)
{
    Celula *aux = busca(indiceInvertido, chave);
    
    //caso ainda nao exista aquela chave no indice invertido
    if(aux == NULL) { 
        Item aux;
        strcpy(aux.chave, chave);
        strcpy(aux.documentos[0], documento);
        aux.n = 1;

        listaInsereFinal(&indiceInvertido->listas[h(chave)], aux);
        indiceInvertido->n++;
        return true;
    }
    //caso ja exista
    else{
        strcpy(aux->pProx->item.documentos[aux->pProx->item.n++], documento);
        return true;
    }

    return false;
}

/**
 * @brief Pesquisa o ponteiro da Celula do item que tem uma chave especificada
 * 
 * @param indiceInvertido onde os dados estao salvos
 * @param chave qual a chave que sera procurada 
 * 
*/
//Retorno o ponteiro apontando para a celula anterior da desejada da lista
Celula * busca(IndiceInvertido *indiceInvertido, Chave chave){
    int i = h(chave);
    if(listaEhVazia(&indiceInvertido->listas[i])) return NULL;

    Celula * aux = indiceInvertido->listas[i].pCabeca;
    
    while(aux->pProx->pProx != NULL && strcmp(chave, aux->pProx->item.chave) != 0) 
        aux = aux->pProx;

    if(!strcmp(chave, aux->pProx->item.chave)) 
        return aux;

    return NULL;
    
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
 * @param chave Todas as chaves que serao utilizadas para pesquisar
 * @param n Numero de chaves que serão utilizadas
 * @param documento documentos que possuem as palavras chaves
 * @param contDocumentos quantidade de documentos com as palavras chaves
 * 
*/
int consulta(IndiceInvertido * indiceInvertido, Chave *chave, int n, NomeDocumento* documento, int *contDocumentos){
    Celula **indicesChaves = (Celula **) malloc(n * sizeof(Celula*));

    for(int i = 0; i < n; i++){
        indicesChaves[i] = busca(indiceInvertido, chave[i])->pProx;
        
        if(indicesChaves[i] == NULL){
            free(*indicesChaves);
            return 0;
        }
    }

    //copiando o nome dos documentos que possuem a primeira palavra(chave) buscada
    *contDocumentos = indicesChaves[0]->item.n;
    
    for(int i=0; i < *contDocumentos; i++)
        strcpy(documento[i], indicesChaves[0]->item.documentos[i]);

    //verificando se os documentos que possuem a primeira palavra(chave), possuem as proximas palavras tambem
    //caso nao possuam, removo ela do vetor de documentos que serao impressos
    bool removerDoc;
    for(int i=1; i < n; i++){ //Passando por todas as palavras(chaves) buscadas
        for(int j=0; j < *contDocumentos; j++){ // Passa pelos documentos do vetor de documentos que serao impressos
            removerDoc = true;

            for(int k=0; k < indicesChaves[i]->item.n; k++){ //Passa por todos os nomes de documentos que possuem x palavra(chave)
                if(strcmp(documento[j], indicesChaves[i]->item.documentos[k]) == 0){
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
void imprimeIndiceInvertido(IndiceInvertido * indiceInvertido){

    for(int i = 0; i < M; i++){
        
        Celula * aux = indiceInvertido->listas[i].pCabeca->pProx;

        while(aux != NULL){

            Item item = aux->item;

            printf("%s -", item.chave);

            for(int j = 0; j < item.n; j++)
                printf(" %s", item.documentos[j]);

            printf("\n");

            aux = aux->pProx;
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
void leEntrada(IndiceInvertido * indiceInvertido, int * nDocumentos)
{
    scanf("%d", nDocumentos);
    getchar();

    int tamMax = (N * NN) + D; //tamanho maximo de caracteres de cada linha da entrada

    char documentoChaves[tamMax]; // armazena a entrada com documento e suas palavras-chaves

    for(int i = 0; i < *nDocumentos; i++){
        fgets(documentoChaves, tamMax, stdin);
    
        documentoChaves[strcspn(documentoChaves, "\n")] = '\0';

        char * token = strtok(documentoChaves, " ");
        char nomeDocumento [D];
        strcpy(nomeDocumento, token);

        token = strtok(NULL, " ");
        while(token != NULL){

            insereDocumento(indiceInvertido, token, nomeDocumento);

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
void leOpcao(IndiceInvertido * indiceInvertido, int nDocumentos){
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
void executaBuscaDoUsuario(IndiceInvertido * indiceInvertido, int nDocumentos, char *palavrasBuscadas){
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
 * @brief Libera todas as listas encadeadas
 * 
 * @param indiceInvertido struct com os dados a serem liberados 
 * 
*/
void liberaListas(IndiceInvertido *indiceInvertido){
    for (int i = 0; i < M; i++)
        listaEsvazia(&indiceInvertido->listas[i]);
   
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

/**
 * @brief Insere um item no final da lista
 * 
 * @param pLista struct de lista
 * @param item struct de item que possue a chave, os documentos e o numero de documentos 
 * 
*/
int listaInsereFinal(Lista *pLista, Item item){
    pLista->pUltimo->pProx = (Celula *) malloc(sizeof(Celula));
    if(pLista->pUltimo->pProx == NULL)
        return 0;

    pLista->pUltimo = pLista->pUltimo->pProx;
    pLista->pUltimo->pProx = NULL;
    pLista->pUltimo->item = item;

    return 1;
}

/**
 * @brief verifica se a lista e vazia
 * 
 * @param pLista struct de lista
 * 
*/
int listaEhVazia(Lista *pLista){
    return pLista->pCabeca->pProx == NULL;
}

/**
 * @brief retira uma celula da primeira posicao da lista
 * 
 * @param pLista struct de lista
 * @param item struct de item que possue a chave, os documentos e o numero de documentos 
 * 
*/
int listaRetiraPrimeiro (Lista *pLista, Item *item){
    if(listaEhVazia(pLista))
        return 0;

    Celula *aux = pLista->pCabeca->pProx;
    *item = aux->item;
    pLista->pCabeca->pProx = aux->pProx;

    free(aux);
    return 1;
}

/**
 * @brief esvazia a lista, desalocando posteriormente a cabeca da mesma
 * 
 * @param pLista struct de lista
 * 
*/
void listaEsvazia(Lista *pLista){
    Item aux;
    while(listaRetiraPrimeiro(pLista, &aux)); //enquanto estiver retornando 1 e porque a lista nao esta vazia

    free(pLista->pCabeca);
}