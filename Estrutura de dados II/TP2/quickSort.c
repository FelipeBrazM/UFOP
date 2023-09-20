#include "quickSort.h"

void quickSort(InfoOrdenacao * infoOrdenacao){

    FILE * ArqLi = fopen(infoOrdenacao->nomeArquivo, "rb+");
    FILE * ArqEi = fopen(infoOrdenacao->nomeArquivo, "rb+");
    FILE * ArqLEs = fopen(infoOrdenacao->nomeArquivo, "rb+");

    QuicksortExterno(&ArqLi, &ArqEi, &ArqLEs, 1, infoOrdenacao->quantidade, infoOrdenacao);

    fclose(ArqLi);
    fclose(ArqEi);
    fclose(ArqLEs);

}


void QuicksortExterno(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir, InfoOrdenacao * infoOrdenacao){
    int i, j;
    
    if(Dir - Esq < 1) return;
    
    TipoArea Area = inicializaArea();

    Particao(ArqLi, ArqEi, ArqLEs, Area, Esq, Dir, &i, &j, infoOrdenacao);
    
    fflush(*ArqLi);
    fflush(*ArqEi);
    fflush(*ArqLEs);

    if(i - Esq < Dir - j){
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, Esq, i, infoOrdenacao);
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, j, Dir, infoOrdenacao);
    }else{
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, j, Dir, infoOrdenacao);
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, Esq, i, infoOrdenacao);
    }
}

//Le o dado do arquivo superior
void LeSup(FILE **ArqLEs, TipoRegistro *UltLido, int *Ls, short *OndeLer, InfoOrdenacao * infoOrdenacao){
    fseek(*ArqLEs, (*Ls - 1) * sizeof(TipoRegistro), SEEK_SET);
    fread(UltLido, sizeof(TipoRegistro), 1, *ArqLEs);
    infoOrdenacao->acessos.qtdLeitura += 1;
    (*Ls)--;
    *OndeLer = false;
}

//Le o dado do arquivo inferior
void LeInf(FILE **ArqLi, TipoRegistro *UltLido, int *Li, short *OndeLer, InfoOrdenacao * infoOrdenacao){
    fread(UltLido, sizeof(TipoRegistro), 1, *ArqLi);
    infoOrdenacao->acessos.qtdLeitura += 1;
    (*Li)++;
    *OndeLer = true;
}

void InserirArea(TipoArea *Area, TipoRegistro *UltLido, int *NRArea, InfoOrdenacao* InfoOrdenacao){
    //Insere UltLido de forma ordenada na Area
    InsereItem(*UltLido, Area, InfoOrdenacao); 
    *NRArea = ObterNumCelOcupadas(Area);
}

//Escreve o item no arquivo superior
void EscreveMax(FILE **ArqLEs, TipoRegistro R, int *Es, InfoOrdenacao * infoOrdenacao){
    fseek(*ArqLEs, (*Es - 1) * sizeof(TipoRegistro), SEEK_SET);
    fwrite(&R, sizeof(TipoRegistro), 1, *ArqLEs);
    infoOrdenacao->acessos.qtdEscrita += 1;
    (*Es)--;
}

//Escreve o item no arquivo inferior
void EscreveMin(FILE **ArqEi, TipoRegistro R, int *Ei, InfoOrdenacao * infoOrdenacao){
    infoOrdenacao->acessos.qtdEscrita += 1;
    fwrite(&R, sizeof(TipoRegistro), 1, *ArqEi); (*Ei)++;
}

//Remove o maior valor do pivo
void RetiraMax(TipoArea *Area, TipoRegistro *R, int *NRArea){
    RetiraUltimo(Area, R);
    *NRArea = ObterNumCelOcupadas(Area);
}

//Remove o menor valor do pivo
void RetiraMin(TipoArea *Area, TipoRegistro *R, int *NRArea){
    RetiraPrimeiro(Area, R);
    *NRArea = ObterNumCelOcupadas(Area);
}

void Particao(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, TipoArea Area, int Esq, int Dir, int *i, int *j, InfoOrdenacao * infoOrdenacao){
    int Ls = Dir, Es = Dir, Li = Esq, Ei = Esq, NRArea = 0;
    double Linf = INT_MIN, Lsup = INT_MAX;
    short OndeLer = true; 
    TipoRegistro UltLido, R;

    fseek(*ArqLi, (Li - 1) * sizeof(TipoRegistro), SEEK_SET);
    fseek(*ArqEi, (Ei - 1) * sizeof(TipoRegistro), SEEK_SET);
    
    *i = Esq - 1; 
    *j = Dir + 1;

    //Lendo ate que os ponteiros de leitura se cruzem
    while(Ls >= Li){
        if(NRArea < TAMAREA - 1){
            if(OndeLer) LeSup(ArqLEs, &UltLido, &Ls, &OndeLer, infoOrdenacao);
            else LeInf(ArqLi, &UltLido, &Li, &OndeLer, infoOrdenacao);

            InserirArea(&Area, &UltLido, &NRArea, infoOrdenacao);
            continue;
        }
        
        //Lendo na alternancia correta
        //Verifica se os ponteiros de leitura e escrita estao juntos para mudar a alternancia da leitura
        if(Ls == Es) LeSup(ArqLEs, &UltLido, &Ls, &OndeLer, infoOrdenacao);
        else if (Li == Ei) LeInf(ArqLi, &UltLido, &Li, &OndeLer, infoOrdenacao);
        else if (OndeLer) LeSup(ArqLEs, &UltLido, &Ls, &OndeLer, infoOrdenacao);
        else LeInf(ArqLi, &UltLido, &Li, &OndeLer, infoOrdenacao);

        //Tratativa do ultimo item lido
        //Caso em que o ultimo elemento vai para o subarquivo A2 (itens superiores ao pivo)
        if(UltLido.nota > Lsup){
            *j = Es; 
            EscreveMax(ArqLEs, UltLido, &Es, infoOrdenacao);
            continue;
        }
        infoOrdenacao->acessos.comparacoesChave += 1;

        //Caso em que o ultimo elemento vai para o subarquivo A1 (itens inferiores ao pivo)
        if(UltLido.nota < Linf){
            *i = Ei; 
            EscreveMin(ArqEi, UltLido, &Ei, infoOrdenacao);
            continue;
        }   
        infoOrdenacao->acessos.comparacoesChave += 1;
    
        //Caso em que o ultimo elemento vai para o pivo
        InserirArea(&Area, &UltLido, &NRArea, infoOrdenacao);
        
        //Verificando qual o menor sub arquivo e escrevendo nele
        if(Ei - Esq < Dir - Es){ 
            RetiraMin(&Area, &R, &NRArea);
            EscreveMin(ArqEi, R, &Ei, infoOrdenacao); 
            Linf = R.nota;
        }
        else{
            RetiraMax(&Area, &R, &NRArea);
            EscreveMax(ArqLEs, R, &Es, infoOrdenacao);
            Lsup = R.nota;
        }   
    }
    
    while(Ei <= Es){
        RetiraMin(&Area, &R, &NRArea);
        EscreveMin(ArqEi, R, &Ei, infoOrdenacao);
    }

}
    