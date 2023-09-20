 #include "arvore_b_estrela.h"
 
void inicializa_b_estrela (TipoApontadorEstrela * Arvore) 
{
    *Arvore = NULL;
}

bool Pesquisa(TipoRegistroEstrela *x, TipoApontadorEstrela *Ap, Resultados *resultados)
{
    int i;
    TipoApontadorEstrela Pag = *Ap;

    if(*Ap == NULL) return false;

    if (Pag->Pt == Interna)
    {
        i = 1;

        resultados->pesquisa.comparacoes +=1;
        while (i < Pag->UU.U0.ni && x->Chave > Pag->UU.U0.ri[i - 1]){
            i++;
            resultados->pesquisa.comparacoes +=1;
        }

        resultados->pesquisa.comparacoes +=1;
        if (x->Chave < Pag->UU.U0.ri[i - 1]) return Pesquisa(x, &Pag->UU.U0.pi[i - 1], resultados);
        else return Pesquisa(x, &Pag->UU.U0.pi[i], resultados);

    }

    i = 1;

    resultados->pesquisa.comparacoes +=1;
    while (i < Pag->UU.U1.ne && x->Chave > Pag->UU.U1.re[i - 1].Chave){
        i++;
        resultados->pesquisa.comparacoes +=1;
    }
    resultados->pesquisa.comparacoes +=1;
    if (x->Chave == Pag->UU.U1.re[i - 1].Chave){
        *x = Pag->UU.U1.re[i - 1];
        return true;
    }
    else return false;
}

void InsereNaPaginaExterna(TipoApontadorEstrela Ap, TipoRegistroEstrela Reg, Resultados *resultados){
    bool NaoAchouPosicao;
    int k;  

    k = Ap->UU.U1.ne; 
    NaoAchouPosicao = (k > 0);

    while(NaoAchouPosicao){
        resultados->preProcessamento.comparacoes +=1;
        if(Reg.Chave > Ap->UU.U1.re[k-1].Chave){
            NaoAchouPosicao = false;
            break;
        }
        Ap->UU.U1.re[k] = Ap->UU.U1.re[k-1];
        k--;
        if(k < 1)
            NaoAchouPosicao = false;
    }

    Ap->UU.U1.re[k] = Reg;
    Ap->UU.U1.ne++;
}

void InsereNaPaginaInterna(TipoApontadorEstrela Ap, TipoChave Reg, TipoApontadorEstrela ApDir, Resultados *resultados){
    bool NaoAchouPosicao;
    int k;

    k = Ap->UU.U0.ni;
    NaoAchouPosicao = (k > 0);

    while (NaoAchouPosicao)
    {
        resultados->preProcessamento.comparacoes += 1;
        if (Reg >= Ap->UU.U0.ri[k - 1])
        {
            NaoAchouPosicao = false;
            break;
        }
        Ap->UU.U0.ri[k] = Ap->UU.U0.ri[k - 1];
        Ap->UU.U0.pi[k+1] = Ap->UU.U0.pi[k];
        k--;
        if (k < 1)
            NaoAchouPosicao = false;
    }
    Ap->UU.U0.ri[k]= Reg;
    Ap->UU.U0.pi[k + 1] = ApDir;
    Ap->UU.U0.ni++;

}

void Ins_b_estrela(TipoRegistroEstrela Reg, TipoApontadorEstrela Ap, short *cresceu, TipoChave *RegRetorno, TipoApontadorEstrela *ApRetorno, Resultados *resultados){
    long i = 1;
    long j;

    TipoApontadorEstrela ApTemp;

    if(Ap->Pt == Externa){
        *cresceu = true;
        *RegRetorno = Reg.Chave;
        *ApRetorno = NULL;

        resultados->preProcessamento.comparacoes += 1;
        while(i < Ap->UU.U1.ne && Reg.Chave > Ap->UU.U1.re[i-1].Chave){
            i++;
            resultados->preProcessamento.comparacoes += 1;
        }

        //caso ja exista o registro na arvore
        resultados->preProcessamento.comparacoes += 1;
        if(Reg.Chave == Ap->UU.U1.re[i-1].Chave){
            *cresceu = false;
            return;
        }

        if(Reg.Chave < Ap->UU.U1.re[i-1].Chave) i--;

        //Se a pagina atual comporta o item a ser inserido
        if(Ap->UU.U1.ne < MMB2){ 
            InsereNaPaginaExterna(Ap, Reg, resultados);
            *cresceu = false;
            return;
        }

        //Overflow: Pagina tem que ser dividida
        //Criando uma nova pagina
        ApTemp = (TipoApontadorEstrela) malloc(sizeof(TipoPaginaEstrela));
        ApTemp->UU.U1.ne = 0;
        ApTemp->Pt = Externa;

        //Verifica para onde a chave ira
        if(i < MB2 + 1){
            //Insere o item na pagina que ja existe
            //Coloca o ultimo registro na nova pagina
            InsereNaPaginaExterna(ApTemp, Ap->UU.U1.re[MMB2 - 1], resultados);
            Ap->UU.U1.ne--;
            //Insere o novo item na pagina atual
            InsereNaPaginaExterna(Ap, Reg, resultados);
        }

        // Inserindo o item que deu o overflow na pagina vizinha
        else InsereNaPaginaExterna(ApTemp, Reg, resultados);
            
        //Colocando os valores excedentes e colocando na pagina nova
        for(j = MB2 + 1; j <= MMB2; j++)
            InsereNaPaginaExterna(ApTemp, Ap->UU.U1.re[j-1], resultados);
            
        *RegRetorno = Ap->UU.U1.re[MB2].Chave;
        Ap->UU.U1.ne = MB2;
        *ApRetorno = ApTemp;

        return;
    }

    else{ //Ap->Pt == Interna
        
        resultados->preProcessamento.comparacoes +=1;
        while(i < Ap->UU.U0.ni && Reg.Chave > Ap->UU.U0.ri[i-1]){ 
            i++;
            resultados->preProcessamento.comparacoes +=1;
        }

        //Verifica se iremos para a sub arvore a esquerda (true) ou direita (false)
        resultados->preProcessamento.comparacoes +=1;
        if(Reg.Chave < Ap->UU.U0.ri[i-1]) i--;

        Ins_b_estrela(Reg, Ap->UU.U0.pi[i], cresceu, RegRetorno, ApRetorno, resultados);

        if(!*cresceu) return;

        //Verifica se a pagina NAO ira crescer, mesmo apos a recursao e adiciona o item no nodo
        if(Ap->UU.U0.ni < MMB){ 
            InsereNaPaginaInterna(Ap, *RegRetorno, *ApRetorno, resultados);
            *cresceu = false;

            return;
        }

        //Overflow: Pagina tem que ser dividida
        //Criando uma nova pagina
        ApTemp = (TipoApontadorEstrela) malloc(sizeof(TipoPaginaEstrela));
        ApTemp->Pt = Interna;
        ApTemp->UU.U0.ni = 0;
        ApTemp->UU.U0.pi[0] = NULL;

        //Verifica para onde a chave ira
        if(i < MB + 1){
            //Insere o item na pagina que ja existe
            //Coloca o ultimo registro na nova pagina
            InsereNaPaginaInterna(ApTemp, Ap->UU.U0.ri[MMB - 1], Ap->UU.U0.pi[MMB], resultados);
            Ap->UU.U0.ni--;
            //Insere o novo item na pagina atual
            InsereNaPaginaInterna(Ap, *RegRetorno, *ApRetorno, resultados);
        }
        
        // Inserindo o item que deu o overflow na pagina vizinha
        else InsereNaPaginaInterna(ApTemp, *RegRetorno, *ApRetorno, resultados);
            
        //Colocando os valores excedentes e colocando na pagina nova
        for(j = MB + 2; j <= MMB; j++)
            InsereNaPaginaInterna(ApTemp, Ap->UU.U0.ri[j-1], Ap->UU.U0.pi[j], resultados);
            
        Ap->UU.U0.ni = MB;
        ApTemp->UU.U0.pi[0] = Ap->UU.U0.pi[MB + 1];
        *RegRetorno = Ap->UU.U0.ri[MB];
        *ApRetorno = ApTemp;
    }
}

void Insere_b_estrela(TipoRegistroEstrela Reg, TipoApontadorEstrela *Ap, Resultados *resultados){
    //caso seja uma nova arvore
    if(*Ap == NULL){
        TipoPaginaEstrela *ApTemp = (TipoPaginaEstrela *)malloc(sizeof(TipoPaginaEstrela));

        ApTemp->Pt = Externa;
        ApTemp->UU.U1.ne = 1;
        ApTemp->UU.U1.re[0] = Reg;
        *Ap = ApTemp;

        return;
    }
    
    short Cresceu;
    TipoChave RegRetorno;
    TipoPaginaEstrela *ApRetorno = NULL, *ApTemp = NULL;

    Ins_b_estrela(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno, resultados);

    // arvore cresce na altura pela raiz
    if (Cresceu){ 
        ApTemp = (TipoPaginaEstrela *)malloc(sizeof(TipoPaginaEstrela));
        ApTemp->Pt = Interna;
        ApTemp->UU.U0.ni = 1;
        ApTemp->UU.U0.ri[0] = RegRetorno;
        ApTemp->UU.U0.pi[1] = ApRetorno;
        ApTemp->UU.U0.pi[0] = *Ap;
        *Ap = ApTemp;
    }

}

int arvore_b_estrela(long chave, char * nomeArquivo, int quantidade, Resultados * resultados){

    resultados->tempoPreProcessamento[0] = clock();

    //Lendo o arquivo
    FILE * arq = fopen(nomeArquivo, "rb");
    if(arq == NULL){
        printErr("Erro na abertura do arquivo\n");
        return 2;
    }

    //Lendo os itens dos arquivos
    TipoRegistroEstrela * registros = (TipoRegistroEstrela *) malloc(quantidade * sizeof(TipoRegistroEstrela));
    fread(registros, quantidade, sizeof(TipoRegistroEstrela), arq);
    resultados->preProcessamento.transferencias += 1;

    //Exibindo os itens do arquivo
    if(resultados->exibirChaves)
        exibirItensArvoreBEstrela(registros, quantidade);

    //Adicionando os itens na arvore
    TipoApontadorEstrela Arvore;
    inicializa_b_estrela(&Arvore);
    for(int i = 0; i < quantidade; i++) Insere_b_estrela(registros[i], &Arvore, resultados);
    
    fclose(arq);
    free(registros);

    resultados->tempoPreProcessamento[1] = clock();

    //Realizando a pesquisa
    resultados->tempoPesquisa[0] = clock();
    bool resultado = Pesquisa(&(resultados->pesquisarEstrela), &Arvore, resultados);
    resultados->tempoPesquisa[1] = clock();

    liberaArvoreBEstrela(Arvore);

    return resultado;
}

void liberaArvoreBEstrela(TipoApontadorEstrela Arvore){
    int i = 0;

    if (Arvore->Pt == Externa){
        free(Arvore);
        
        return;
    }

    while (i <= Arvore->UU.U0.ni) {
        liberaArvoreBEstrela(Arvore->UU.U0.pi[i]);

        if (i == Arvore->UU.U0.ni){
            free(Arvore);
            break; //break para sair do while e nao fazer uma comparacao com a Arvore que foi liberada
        }

        i++;
    } 
}

void exibirItensArvoreBEstrela(TipoRegistroEstrela * registros, int quantidade){
    for(int i = 0; i < quantidade; i++)
        printf("%ld\n", registros[i].Chave);
}