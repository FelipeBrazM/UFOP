#include "arvore_b.h"


void  inicializa (TipoApontador * Arvore){
    *Arvore = NULL;
}

bool pesquisa_arvore_b (TipoRegistro *x, TipoApontador Ap, Resultados *resultados){
    if(Ap == NULL) return false;

    long i = 1;
    resultados->pesquisa.comparacoes += 1;
    while(i < Ap->n && x->Chave > Ap->r[i-1].Chave){
        i++;
        resultados->pesquisa.comparacoes += 1;
    }

    resultados->pesquisa.comparacoes += 1;
    if(x->Chave == Ap->r[i-1].Chave){
        *x = Ap->r[i-1];
        resultados->pesquisa.comparacoes += 1;
        return true;
    }

    resultados->pesquisa.comparacoes += 1;
    if(x->Chave < Ap->r[i-1].Chave) return pesquisa_arvore_b(x, Ap->p[i-1], resultados);

    else return pesquisa_arvore_b(x, Ap->p[i], resultados);
}

void imprime (TipoApontador arvore){
    if(arvore == NULL) return;

    int i = 0;
    while(i <= arvore->n){
        imprime(arvore->p[i]);
        
        if(i != arvore->n)
            printf("%ld ", arvore->r[i].Chave);

        i++;
    }
}

void InsereNaPagina (TipoApontador Ap, TipoRegistro Reg, TipoApontador ApDir, Resultados *resultados){
    bool NaoAchouPosicao;
    int k = Ap->n; 
    NaoAchouPosicao = (k > 0);
    
    //Procura em qual posicao o item devera ser inserido na pagina
    while(NaoAchouPosicao){
        resultados->preProcessamento.comparacoes += 1;
        if(Reg.Chave >= Ap->r[k-1].Chave){
            NaoAchouPosicao = false;
            break;
        }
        Ap->r[k] = Ap->r[k-1];
        Ap->p[k+1] = Ap->p[k];
        k--;
        if(k < 1)
            NaoAchouPosicao = false;
    }

    Ap->r[k] = Reg;
    Ap->p[k+1] = ApDir;
    Ap->n++;
}

//Percorre a arvore procurando qual o local que deve inserir o item
void Ins(TipoRegistro Reg, TipoApontador Ap, short *cresceu, TipoRegistro *RegRetorno, TipoApontador *ApRetorno, Resultados *resultados){
    long i = 1; //Onde o item deve ser inserido
    long j;
    
    TipoApontador ApTemp;
    
    //Verifica se a arvore esta vazia ou se chegou no nodo folha
    if(Ap == NULL){
        *cresceu = true;
        (*RegRetorno) = Reg;
        (*ApRetorno) = NULL;

        return;
    }

    //Realiza uma pesquisa na pagina para saber se ele existe nela
    resultados->preProcessamento.comparacoes += 1;
    while(i < Ap->n && Reg.Chave > Ap->r[i-1].Chave){
        i++;
         resultados->preProcessamento.comparacoes += 1;
    }

    resultados->preProcessamento.comparacoes += 1;
    if(Reg.Chave == Ap->r[i-1].Chave){
        //!Erro: Registro ja esta presente
        *cresceu = false;
        return;
    }

    //Verifica se iremos para a sub arvore a esquerda (true) ou direita (false)
    resultados->preProcessamento.comparacoes += 1;
    if(Reg.Chave < Ap->r[i-1].Chave) i--;
    

    Ins(Reg, Ap->p[i], cresceu, RegRetorno, ApRetorno, resultados);

    //Quando passar por este if, significa que chegou no nodo folha, entao podemos inserir
    //Tambem ira passar quando o no filho deu overflow e a arvore ira crescer, pois um item subiu
    if(!*cresceu) return;
        
    //Verifica se a pagina NAO ira crescer, mesmo apos a recursao e adiciona o item no nodo
    if(Ap->n < MM){ 
        InsereNaPagina(Ap, *RegRetorno, *ApRetorno, resultados);
        *cresceu = false;

        return;
    }

    //Overflow: Pagina tem que ser dividida
    //Criando uma nova pagina
    ApTemp = (TipoApontador) malloc(sizeof(TipoPagina));
    ApTemp->n = 0;
    ApTemp->p[0] = NULL;

    //Verifica para onde a chave ira
    if(i < M + 1){
        //Insere o item na pagina que ja existe
        //Coloca o ultimo registro na nova pagina
        InsereNaPagina(ApTemp, Ap->r[MM - 1], Ap->p[MM], resultados);
        Ap->n--;
        //Insere o novo item na pagina atual
        InsereNaPagina(Ap, *RegRetorno, *ApRetorno, resultados);
    }
    
    // Inserindo o item que deu o overflow na pagina vizinha
    else InsereNaPagina(ApTemp, *RegRetorno, *ApRetorno, resultados);
        
    //Colocando os valores excedentes e colocando na pagina nova
    for(j = M + 2; j <= MM; j++)
        InsereNaPagina(ApTemp, Ap->r[j-1], Ap->p[j], resultados);
        
    Ap->n = M;
    ApTemp->p[0] = Ap->p[M + 1];
    *RegRetorno = Ap->r[M];
    *ApRetorno = ApTemp;
}

void Insere(TipoRegistro Reg, TipoApontador *Ap, Resultados * resultados){
    short Cresceu;
    TipoRegistro RegRetorno;
    TipoPagina *ApRetorno, *ApTemp;

    Ins(Reg, *Ap, &Cresceu,&RegRetorno, &ApRetorno, resultados);
    
    //Verifica se a raiz da arvore vai crescer a raiz
    if(Cresceu){
        ApTemp = (TipoPagina *) malloc(sizeof(TipoPagina));
        ApTemp->n = 1;
        ApTemp->r[0] = RegRetorno;
        ApTemp->p[1] = ApRetorno;
        ApTemp->p[0] = *Ap; 
        *Ap = ApTemp;
    }
}


int arvore_b(char * nomeArquivo, int quantidade, Resultados * resultados){

    //! Pre-Processamento
    resultados->tempoPreProcessamento[0] = clock();

    //Criando a árvore
    FILE * arq = fopen(nomeArquivo, "rb");
    if(arq == NULL){
        printErr("Erro na abertura do arquivo\n");
        return 2;
    }

    //Lendo todos os registros do arquivo
    TipoRegistro * registros = (TipoRegistro *) malloc(quantidade * sizeof(TipoRegistro));
    fread(registros, quantidade, sizeof(TipoRegistro), arq);
    resultados->preProcessamento.transferencias += 1;

    TipoApontador Arvore;
    inicializa(&Arvore);

    //Inserir os itens na arvore B
    for(int i = 0; i < quantidade; i++)
        Insere(registros[i], &Arvore, resultados);
    
    fclose(arq);
    free(registros);

    resultados->tempoPreProcessamento[1] = clock();

    //Realizando a pesquisa
    resultados->tempoPesquisa[0] = clock();
    bool resultado = pesquisa_arvore_b(&(resultados->pesquisar), Arvore, resultados);

    resultados->tempoPesquisa[1] = clock();

    liberaArvoreB(Arvore);

    return resultado;
    
}

void liberaArvoreB(TipoApontador Arvore){
    int i = 0;

    if (Arvore == NULL) return;

    while (i <= Arvore->n) {
        liberaArvoreB(Arvore->p[i]);

        if (i == Arvore->n){
            free(Arvore);
            break; //break para sair do while e nao fazer uma comparacao com a Arvore que foi liberada
        }         

        i++;
    } 
}