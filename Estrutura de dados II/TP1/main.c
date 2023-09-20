#include "menus.h"
#include <time.h>

int main(int argc, char * argv[]){

    if(argc < 5 || argc > 6){
        printf(RED("Quantidade de parâmetros inválida\n"));
        printf("\t./nome_executavel <metodo> <quantidade_de_itens> <situacao> <chave> [-P]");
        return 0;
    }

    int metodo = atoi(argv[1]);
    int quantidade = atoi(argv[2]);
    int situacao = atoi(argv[3]);
    bool p = false;
    
    char chaveArg[10];
    strcpy(chaveArg, argv[4]);
    
    //Verifica se o -P foi passado como argumento
    if(argc == 6){
        if(!(strcmp(argv[5], "-P")))
            p = true;
    }

    if(!verificaInputsValidos(metodo, quantidade, situacao)) return 0;   

    char nomeArquivo [100];
    geraNomeArquivo(argv[2], situacao, nomeArquivo);

    //Caso a pesquisa seja de um unico item
    if(strcmp(chaveArg, "-a") != 0){

        long chave = converteChave(chaveArg);

        Resultados resultado;

        resultado.metodo = metodo;
        resultado.pesquisar.Chave = chave;
        resultado.pesquisarEstrela.Chave = chave;

        resultado.preProcessamento.transferencias = 0;
        resultado.preProcessamento.comparacoes = 0;

        resultado.pesquisa.transferencias = 0;
        resultado.pesquisa.comparacoes = 0;

        resultado.exibirChaves = p;
        resultado.resultadoPesquisa = selecionaMetodo(metodo, chave, nomeArquivo, quantidade, &resultado);

        if(resultado.resultadoPesquisa != 2)
            imprimeResultados(&resultado);

    }
    //Caso a pesquisa seja de 10 itens automatica
    else{

        Resultados resultados [10];
        srand(time(NULL));

        //Verifica se podem ser geradas chaves aleatorios com os itens do arquivo necessario
        if(gerarNumerosAleatorios(nomeArquivo, quantidade, resultados)){
            //Pesquisa a chave de acordo com o metodo
            for(int i = 0; i < 10; i++){
                resultados[i].exibirChaves = p;

                resultados[i].preProcessamento.transferencias = 0;
                resultados[i].preProcessamento.comparacoes = 0;

                resultados[i].pesquisa.transferencias = 0;
                resultados[i].pesquisa.comparacoes = 0;

                resultados[i].metodo = metodo;
                
                resultados[i].resultadoPesquisa = selecionaMetodo(metodo, resultados[i].pesquisar.Chave, nomeArquivo, quantidade, &resultados[i]);

                //Arquivo inexistente
                if(resultados[i].resultadoPesquisa == 2)
                    break;

                imprimeResultados(&(resultados[i]));
            }

            calculaMediaExecucoes(resultados);
        }
        else
            printErr("Arquivo necessário para o método encontra-se inexistente\n");

    }

    if(metodo == 2)
        remove("abp.bin");

    return 0;
}