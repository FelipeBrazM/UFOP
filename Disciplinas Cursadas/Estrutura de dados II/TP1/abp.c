#include "abp.h"

void constroiArvore(FILE * arq, FILE *arqAbp, Resultados * resultados){

    TipoRegistro itemLeitura;
    int pos = 1;
    //Le os dados do arquivo original e passa para o arquivo da arvore binaria de pesquisa
    resultados->preProcessamento.transferencias +=1;
    while ((fread(&itemLeitura, sizeof(TipoRegistro), 1, arq)) != 0){

        //Exibindo todas as chaves do arquivo
        if(resultados->exibirChaves)
            printf("%ld\n", itemLeitura.Chave);


        //Inserindo os itens no arquivo da ABP
        resultados->preProcessamento.transferencias +=1;

        TipoItem itemInserir;
        itemInserir.item = itemLeitura;
        itemInserir.dir = -1;
        itemInserir.esq = -1;
        fseek(arqAbp, 0, SEEK_END);
        fwrite(&itemInserir, sizeof(TipoItem), 1, arqAbp);
        atualizaPonteiros(arqAbp, &itemInserir, resultados);
        pos++;
    }
}


void atualizaPonteiros(FILE *arq, TipoItem *itemInserir, Resultados * resultados)
{
    // Verificando a quantidade de itens no arquivo
    fseek(arq, 0, SEEK_END);
    long qtdItensArquivo = ftell(arq) / sizeof(TipoItem); //vai ser a "posicao" do arquivo que o novo item esta
    fseek(arq, 0, SEEK_SET);

    //Nao e necessario atualizar ponteiros quando tem-se apenas um item
    if(qtdItensArquivo == 1) return;
    
    TipoItem aux;
    
    //Caminhando o ponteiro do arquivo ate o local onde devera alterar o ponteiro da arvore
    long ponteiro = 1;
    long desloc;
    
    //procura o ponteiro que precisa ser atualizado com o numero da linha do item que foi inserido
    do{
        //Calcula o deslocamento necessario, a partir do inicio do arquivo, para chegar ao no filho do pai
        desloc = (ponteiro - 1) * sizeof(TipoItem);
        fseek(arq, desloc, SEEK_SET);
        fread(&aux, sizeof(TipoItem), 1, arq);
        resultados->preProcessamento.transferencias +=1;
        //Caminhando o ponteiro pelo arquivo ate encontrar uma "folha" = (-1)
        ponteiro = (itemInserir->item.Chave > aux.item.Chave) ? aux.dir : aux.esq;
        resultados->preProcessamento.comparacoes +=1;

    }while(ponteiro != -1);

    //Voltando uma posicao para tratar o "no" correto
    fseek(arq, -(sizeof(TipoItem)), SEEK_CUR);
    
    //Compara novamente as chaves para a insercao da linha
    resultados->preProcessamento.comparacoes += 1;
    if(itemInserir->item.Chave > aux.item.Chave) aux.dir = qtdItensArquivo;
    else aux.esq = qtdItensArquivo;   
    fwrite(&aux, sizeof(TipoItem), 1, arq); //insere a linha
    return;
}

bool pequisarAbp(FILE *arq, TipoRegistro *pesquisado, Resultados * resultados){
    TipoItem aux;

    long ponteiro = 1;
    long desloc;
    
    do{
        //Calcula o deslocamento necessario, a partir do inicio do arquivo, para chegar ao no filho do pai
        desloc = (ponteiro - 1) * sizeof(TipoItem);
        fseek(arq, desloc, SEEK_SET);
        fread(&aux, sizeof(TipoItem), 1, arq);
        resultados->pesquisa.transferencias += 1;

        //Caminhando o ponteiro pelo arquivo ate encontrar uma "folha" = (-1)
        if(pesquisado->Chave == aux.item.Chave){
            resultados->pesquisa.comparacoes += 1;
            *pesquisado = aux.item;
            return true;
        }
        ponteiro = (pesquisado->Chave > aux.item.Chave) ? aux.dir : aux.esq;
        resultados->pesquisa.comparacoes += 1;

    }while(ponteiro != -1);
    
    return false;
}

int arvore_binaria_de_pesquisa(char * nomeArquivo, Resultados * resultados){
    //! Pré processamento
    resultados->tempoPreProcessamento[0] = clock();

    //tentando abrir arquivo para pesquisa
    FILE *arq = fopen(nomeArquivo, "rb");
    if (arq == NULL){
        printErr("Erro na abertura do arquivo para construção da árovre\n");
        return 2;
    }

    //abrindo como "rb" para verificar se a arvore ja existe
    //dessa forma nao cria a mesma abp mais de uma vez
    FILE *arqAbp = fopen("abp.bin", "rb");

    if(arqAbp == NULL){ //caso a arvore nao exista
        arqAbp = fopen("abp.bin", "wb+"); 

        if (arqAbp == NULL){
            printErr("Erro na abertura do arquivo\n");
            fclose(arq);
            return 2;
        }

        constroiArvore(arq, arqAbp, resultados);
    }

    fseek(arq, 0, SEEK_SET);
    fseek(arqAbp, 0, SEEK_SET);
    
    resultados->tempoPreProcessamento[1] = clock();

    //!Pesquisando  
    resultados->tempoPesquisa[0] = clock();  
    bool resultado = pequisarAbp(arqAbp, &(resultados->pesquisar), resultados);

    fclose(arq);
    fclose(arqAbp);

    resultados->tempoPesquisa[1] = clock();

    return resultado;
}