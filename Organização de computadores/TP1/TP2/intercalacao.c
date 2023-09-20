#include "intercalacao.h"

void gerarFitas(Fita * fitas){
    for(int i = 0; i < 40; i++){
        fitas[i].n_blocos = 0;
        //Define o tipo de fita
        fitas[i].tipo = i < 20 ? ENTRADA : SAIDA;

        char nomeArquivo[20];
        sprintf(nomeArquivo, "fitas/fita_%d.bin", i+1);
        fitas[i].arq = fopen(nomeArquivo, "wb+");

        //Gerando um vetor que possui a quantidade de itens de cada bloco da fita
        //O vetor comeca com zero posicoes e vai sendo incrementado ao possuir mais blocos na fita
        fitas[i].qtdItensBloco = malloc(0);
    }
}

void fecharArquivos(Fita * fitas){
    for(int i = 0; i < 40; i++){
        fclose(fitas[i].arq);
    }
}

bool todosMarcados(RegistroParaSubstituicao* registros){
    for (int i = 0; i < 20; i++)
        if(registros[i].marcado == false)
            return false;
    
    return true;
}

void desmarcarRegistros(RegistroParaSubstituicao* registros){
    for(int i = 0; i < 20; i++)
        registros[i].marcado = false;
}

void atualizaStatusDeBlocos(Fita* fita, int numItensUltimoBloco){
    //atualizando a fita atual em relacao a qtd de blocos e numero de itens daquele bloco
    fita->n_blocos++;
    fita->qtdItensBloco = realloc(fita->qtdItensBloco, fita->n_blocos * sizeof(int));
    fita->qtdItensBloco[fita->n_blocos - 1] = numItensUltimoBloco;
}

int procuraMenor(RegistroParaSubstituicao* registros, int n, InfoOrdenacao *InfoOrdenacao){
    RegistroParaSubstituicao aux = registros[0];
    int posMenor = 0;

    for (int i = 1; i < n; i++){
        if(compare(aux, registros[i], InfoOrdenacao)){
            posMenor = i;
            aux = registros[i];
        }
    }
    
    return posMenor;
}

void gerarSelecaoSubstituicao(Fita * fitas, InfoOrdenacao *infoOrdenacao){
    FILE * arq = fopen(infoOrdenacao->nomeArquivo, "rb");
    RegistroParaSubstituicao blocoPorSubstituicao[20]; //Memoria Interna

    int qtdInicialParaLer;
    int qtdItensQueFaltam = infoOrdenacao->quantidade;
    
    qtdInicialParaLer = qtdItensQueFaltam >= 20 ? 20 : qtdItensQueFaltam;
    qtdItensQueFaltam -= qtdInicialParaLer;

    //vetor auxiliar de registros para nao precisar ler 1 por 1 no arquivo
    TipoRegistro aux[20];

    fread(aux, sizeof(TipoRegistro), qtdInicialParaLer, arq);
    infoOrdenacao->acessos.qtdLeituraGeracaoBlocos += 1;

    //copiando os registros do vetor auxiliar para o vetor que representa a memoria interna
    for (int i = 0; i < qtdInicialParaLer; i++){
        blocoPorSubstituicao[i].registro = aux[i];
        blocoPorSubstituicao[i].marcado = false;
    }

    int fitaAtual = 0; //fita atual de entrada
    TipoRegistro registroRetirado;
    RegistroParaSubstituicao proxRegistro;
    int numItensDoBloco = 0;
    int posMenor;

    for(int i = 0; i < qtdItensQueFaltam; i++){     
        posMenor = procuraMenor(blocoPorSubstituicao, 20, infoOrdenacao);

        //retira o menor registro em nota do vetor e escreve na fita
        registroRetirado = blocoPorSubstituicao[posMenor].registro;

        fwrite(&registroRetirado, sizeof(TipoRegistro), 1, fitas[fitaAtual%20].arq);
        infoOrdenacao->acessos.qtdEscritaGeracaoBlocos += 1;
        numItensDoBloco++;

        //le o proximo registro do provao aleatorio e verifica se e menor que o ultimo que saiu
        fread(&proxRegistro.registro, sizeof(TipoRegistro), 1, arq);
        infoOrdenacao->acessos.qtdLeituraGeracaoBlocos += 1;
        
        if(proxRegistro.registro.nota < registroRetirado.nota)
            proxRegistro.marcado = true;
        else
            proxRegistro.marcado = false;

        infoOrdenacao->acessos.comparacoesChave++;

        //inserindo o registro na memoria interna
        blocoPorSubstituicao[posMenor] = proxRegistro;

        if(todosMarcados(blocoPorSubstituicao)){
            desmarcarRegistros(blocoPorSubstituicao);

            //atualizando a fita atual em relacao a qtd de blocos e numero de itens daquele bloco
            atualizaStatusDeBlocos(&fitas[fitaAtual%20], numItensDoBloco);

            fitaAtual++; //vai para proxima fita
            numItensDoBloco = 0;
        }     
    }

    //ordenando os registros que sobraram na memoria interna
    quicksort_interno_SelecaoSubs(blocoPorSubstituicao, 0, qtdInicialParaLer-1, infoOrdenacao);

    //escrever o resto dos itens presentes na memoria interna
    for (int i = 0; i < qtdInicialParaLer; i++){
        if(blocoPorSubstituicao[i].marcado){
            desmarcarRegistros(blocoPorSubstituicao);
            
            //atualizando a fita atual em relacao a qtd de blocos e numero de itens daquele bloco
            atualizaStatusDeBlocos(&fitas[fitaAtual%20], numItensDoBloco);
            
            fitaAtual++; //vai para proxima fita
            numItensDoBloco = 0;
        }

        fwrite(&blocoPorSubstituicao[i].registro, sizeof(TipoRegistro), 1, fitas[fitaAtual%20].arq);
        infoOrdenacao->acessos.qtdEscritaGeracaoBlocos += 1;
        numItensDoBloco++;
    }
    
    //atualizando a fita atual em relacao a qtd de blocos e numero de itens daquele bloco
    atualizaStatusDeBlocos(&fitas[fitaAtual%20], numItensDoBloco);

    fclose(arq);
}

void gerarBlocos(Fita * fitas, InfoOrdenacao * infoOrdenacao){

    FILE * arq = fopen(infoOrdenacao->nomeArquivo, "rb");
    TipoRegistro registrosInterno [20]; //Memoria Interna

    //Verificando a quantidade de blocos que serao lidos
    int qtdBlocos = (int) ceil(infoOrdenacao->quantidade / 20.0);
    int qtdItensALer;
    int qtdItensQueFaltam = infoOrdenacao->quantidade;

    int i;
    //Transferindo os dados para as fitas
    for(i = 0; i < qtdBlocos; i++){
        //Verificando se a quantidade de itens a ser lido eh menor que 20, se for, ler somente a quantidade que falta
        qtdItensALer = qtdItensQueFaltam >= 20 ? 20 : qtdItensQueFaltam;
        qtdItensQueFaltam -= qtdItensALer;
        
        //Lendo os dados, salvando na estrutura interna e ordenando pela nota
        fread(registrosInterno, sizeof(TipoRegistro), qtdItensALer, arq);
        quicksort_interno(registrosInterno, 0, qtdItensALer-1, infoOrdenacao);
        infoOrdenacao->acessos.qtdLeituraGeracaoBlocos += 1;

        //Escrevendo o dado na fita
        fitas[i%20].n_blocos ++;
        fwrite(registrosInterno, sizeof(TipoRegistro), qtdItensALer, fitas[i%20].arq);
        infoOrdenacao->acessos.qtdEscritaGeracaoBlocos += 1;
    }

    //Setando a quantidade de todos os blocos para serem 20
    for(i = 0; i < 20; i++){
        free(fitas[i].qtdItensBloco);
        fitas[i].qtdItensBloco = malloc(fitas[i].n_blocos * sizeof(int));

        for (int j = 0; j < fitas[i].n_blocos; j++)
            fitas[i].qtdItensBloco[j] = 20;
    }

    //Alterando a quantidade de itens no ultimo bloco ja que ele pode ter menos de 20 itens
    int fitaDoUltimoBloco = (qtdBlocos % 20) == 0 ? 19 : (qtdBlocos % 20) - 1;
    int blocos = fitas[fitaDoUltimoBloco].n_blocos; //num blocos da fita do ultimo bloco
    fitas[fitaDoUltimoBloco].qtdItensBloco[blocos-1] = infoOrdenacao->quantidade % 20 == 0 ? 20 : infoOrdenacao->quantidade % 20;

    fclose(arq);
}

void setPointeirosInicio(Fita * fitas){
    for(int i = 0; i < 40; i++){
        rewind(fitas[i].arq);
    }

}

Intercalacao * gerarFitasIntercalacao(int qtdFitas){
    Intercalacao * fitasIntercalacao = (Intercalacao*) malloc(qtdFitas * sizeof(Intercalacao));
    for(int i = 0; i < qtdFitas; i++){
        fitasIntercalacao[i].qtdItensLidos = 0;
        fitasIntercalacao[i].fitaAtiva = false;
    }

    return fitasIntercalacao;
}

void tornarFitasAtivas(Intercalacao * dadosIntercalacao, int qtdFitas){
    for(int i = 0; i < qtdFitas; i++)
        dadosIntercalacao[i].fitaAtiva = true;
}

bool todosOsDadosLidos(Intercalacao * intercalacao, int qtdFitas){
    //Verifica se todos os dados dos blocos foram lidos
    for(int i = 0; i < qtdFitas; i++){
        if(intercalacao[i].fitaAtiva)
            return false;
    }

    return true;
}

//Le o primeiro item dos blocos e retorna a posicao do item de menor elemento
void lerPrimeirosDados(int inicio, Intercalacao * dadosIntercalacao, Fita * fitas, int qtdFitas, InfoOrdenacao * infoOrdenacao){
    for(int i = 0; i < qtdFitas; i++ ){
        fread(&dadosIntercalacao[i].dadoLido, sizeof(TipoRegistro), 1, fitas[i + inicio].arq);
        dadosIntercalacao[i].qtdItensLidos++;
        infoOrdenacao->acessos.qtdLeitura += 1;
    }
}

int procurarMenorValor(Intercalacao * dadosIntercalacao, int qtdFitas, InfoOrdenacao * infoOrdenacao){
    TipoRegistro temp;
    int posicaoMenorNota=qtdFitas;

    //procurando a primeira fita ativa
    for(int i = 0; i < qtdFitas; i++){
        if(dadosIntercalacao[i].fitaAtiva){
            posicaoMenorNota = i;
            temp = dadosIntercalacao[i].dadoLido;
            break;
        }
    }

    //Procurando no restante das fitas o dado com a menor nota
    for(int i = posicaoMenorNota + 1; i < qtdFitas; i++){
        infoOrdenacao->acessos.comparacoesChave += 1;
        if(dadosIntercalacao[i].fitaAtiva && dadosIntercalacao[i].dadoLido.nota < temp.nota){
            posicaoMenorNota = i;
            temp = dadosIntercalacao[i].dadoLido;
        }
    }
    return posicaoMenorNota;
}

void escreverDadosOrdenados(Fita * fitas, InfoOrdenacao * infoOrdenacao, int fitaSaida){
    setPointeirosInicio(fitas);
    
    FILE * arqDestino = fopen(infoOrdenacao->nomeArquivo, "wb");

    if(arqDestino == NULL){
        printf("Não foi possível abrir o arquivo onde os dados serão salvos\n");
        return;
    }

    //A proposta do trabalho impede que sejam lidos mais de 20 itens de uma so vez
    // Lendo 20 dados, no maximo, e ja escrevendo no arquivo de saida
    TipoRegistro buffer[20];
    size_t bytesLidos;

    infoOrdenacao->acessos.qtdLeitura += 1;
    while ((bytesLidos = fread(buffer, sizeof(TipoRegistro), 20, fitas[fitaSaida].arq)) > 0){
        infoOrdenacao->acessos.qtdLeitura += 1;
        fwrite(buffer, sizeof(TipoRegistro), bytesLidos, arqDestino);
        infoOrdenacao->acessos.qtdEscrita += 1;
    }
    
    fclose(arqDestino);
}

void intercalarBlocos(Fita * fitas, InfoOrdenacao * infoOrdenacao){

    enum TipoFita tipoFitaLeitura = ENTRADA;
    int entrada = 0, saida = 20;

    //marca qual sera a fita de saida que recebera o bloco resultante da passada atual da intercalacao
    int fitaSaida, passada;
    
    //Verificando a quantidade total de blocos gerados inicialmente
    int qtdBlocos = 0;
    for (int i = entrada; i < entrada + 20; i++)
            qtdBlocos += fitas[i].n_blocos;
    
    //Executando ate que tenhamos somente um bloco
    while(qtdBlocos > 1){
        setPointeirosInicio(fitas);   
        
        //Verificando a quantidade de fitas com blocos que irao participar da passada inicial, 
        //afim de evitar que fitas sem conteudo sejam varridas
        int qtdFitas = 0;
        for (int i = entrada; i < entrada+20; i++)
            if(fitas[i].n_blocos > 0)
                qtdFitas++;

        passada = 1;
        
        //executa todas as passadas de intercalacao nas fitas de entrada
        while(qtdFitas > 0){
            //Gerando os registros que terao os dados da intercalacao
            Intercalacao * dadosIntercalacao = gerarFitasIntercalacao(qtdFitas);
            tornarFitasAtivas(dadosIntercalacao, qtdFitas);

            //Calculando qual ser a fita de saida sendo que ela pode ocupar as vinte e retornar para a primeira
            fitaSaida = ((saida + passada - 1) % 20) + saida;

            //Lendo o primeiro registro de cada bloco
            lerPrimeirosDados(entrada, dadosIntercalacao, fitas, qtdFitas, infoOrdenacao);
            
            int posicaoMenorNota;

            int qtdDadosEscritos = 0;

            //representa 1 passada
            //Lendo todos os dados e escrevendo o que tiver a menor chave
            while(todosOsDadosLidos(dadosIntercalacao, qtdFitas) == false){
                posicaoMenorNota = procurarMenorValor(dadosIntercalacao, qtdFitas, infoOrdenacao);

                //Escrevendo o item de menor chave na fita de saida
                TipoRegistro * escrever = &dadosIntercalacao[posicaoMenorNota].dadoLido; 
                
                fwrite(escrever, sizeof(TipoRegistro), 1, fitas[fitaSaida].arq);
                qtdDadosEscritos++;
                infoOrdenacao->acessos.qtdEscrita += 1;

                //desativando a fita caso todos os seus itens ja tenham sido lidos
                if(dadosIntercalacao[posicaoMenorNota].qtdItensLidos == fitas[entrada+posicaoMenorNota].qtdItensBloco[passada-1]){
                    dadosIntercalacao[posicaoMenorNota].fitaAtiva = false;
                    //decrementando o numero de blocos daquela fita, tendo em vista que ela ira virar uma fita de saida posteriormente
                    fitas[entrada+posicaoMenorNota].n_blocos--;
                }

                //Lendo o proximo item da fita onde o registro retirado eh proveniente, ja que a fita ainda estiver ativa
                else{
                    fread(&dadosIntercalacao[posicaoMenorNota].dadoLido, sizeof(TipoRegistro), 1, fitas[posicaoMenorNota+entrada].arq);
                    dadosIntercalacao[posicaoMenorNota].qtdItensLidos++;
                    infoOrdenacao->acessos.qtdLeitura += 1;
                }
            }

            passada++;

            //Alterando o vetor que contem a quantidade de itens em cada bloco
            fitas[fitaSaida].n_blocos++;
            int numBlocos = fitas[fitaSaida].n_blocos;
            fitas[fitaSaida].qtdItensBloco = realloc(fitas[fitaSaida].qtdItensBloco, numBlocos * sizeof(int));
            fitas[fitaSaida].qtdItensBloco[numBlocos-1] = qtdDadosEscritos;

            free(dadosIntercalacao);

            //Verificando a quantidade de fitas com blocos que irao participar da proxima passada
            qtdFitas = 0;
            for (int i = entrada; i < entrada+20; i++)
                if(fitas[i].n_blocos > 0)
                    qtdFitas++;
        }

        //Se a fita atual for de leitura, a procima sera de saida e vice versa
        tipoFitaLeitura = tipoFitaLeitura == ENTRADA ? SAIDA : ENTRADA;

        //Definindo quais fitas serao as de entrada e saida
        if(tipoFitaLeitura == ENTRADA){entrada = 0;  saida = 20;}
        else                          {entrada = 20; saida =  0;}  

        //Calculando a quantidade de blocos
        qtdBlocos = 0;
        for (int i = entrada; i < entrada + 20; i++)
            qtdBlocos += fitas[i].n_blocos;
    }

    //copia saida final para o arquivo quer se quer ordenadar
    escreverDadosOrdenados(fitas, infoOrdenacao, fitaSaida);

}

void intercalacao_balanceada(InfoOrdenacao * infoOrdenacao){
    
    Fita fitas[40];
    gerarFitas(fitas);

    printf("Gerando blocos.\n");
    if(infoOrdenacao->metodo == BALANCEADA_BLOCO_OI) gerarBlocos(fitas, infoOrdenacao);
    else gerarSelecaoSubstituicao(fitas, infoOrdenacao);

    setPointeirosInicio(fitas);

    printf("Realizando a intercalação.\n");
    intercalarBlocos(fitas, infoOrdenacao);

    for(int i = 0; i < 40; i++)
        free(fitas[i].qtdItensBloco);

    fecharArquivos(fitas);
}
