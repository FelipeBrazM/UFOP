//Felipe Braz Marques 22.1.4030

#include "function.h"

void menuPrincipal(){
    
    printf("\x1b[33m""\nBem vindo ao Jogo da Velha\n\n""\x1b[0m");
    printf("\x1b[32m""0. Sair do jogo\n");
    printf("1. Começar um novo jogo\n");
    printf("2. Continuar um jogo salvo\n");
    printf("3. Continuar o jogo atual\n");
    printf("4. Exibir o ranking\n");
    printf("\nDurante o jogo digite \"voltar\" para retornar ao menu.\n\n""\x1b[0m");
}

void inicializarMatriz(char mat[][3]){
    for (int i = 0; i < 3; i++){
        for(int j = 0; j< 3; j++){
            mat[i][j] = ' ';
        }
        }
}

void printaMatriz(char mat[][3]){
        
    printf("\u250F");
    for(int i = 0; i < 4; i++){
        printf("\u2501\u2501\u2501");
        if(i != 3)
            printf("\u2533");
        else{
            printf("\u2513");
        }
    }
    printf("\n");
    printf("\u2503   ");
    for(int i = 0; i < 3; i++){
        printf("\u2503 %d ", i+1);
    }
    printf("\u2503");
    printf("\n");

    printf("\u2523");
    for(int i = 0; i < 4; i++){
        printf("\u2501\u2501\u2501");
        if(i != 3)
            printf("\u254B");
        else{
            printf("\u252B");
        }
    }
    printf("\n");

    for(int i = 0; i < 3; i++){
        printf("\u2503 %d ", i+1);
        for(int j = 0; j < 3; j++){
            printf("\u2503 %c ", mat[i][j]);
        }
        printf("\u2503");
        printf("\n");
        if(i != 2){
            printf("\u2523");
            for(int j = 0; j < 4; j++){
                printf("\u2501\u2501\u2501");
                if(j != 3)
                    printf("\u254B");
                else{
                    printf("\u252B");
                }
            }
        }
        else{
            printf("\u2517");
            for(int j = 0; j < 4; j++){
                printf("\u2501\u2501\u2501");
                if(j != 3)
                    printf("\u253B");
                else{
                    printf("\u251B");
                }
            }
        }
        printf("\n");
    }
}

void pegaJogadores(char *jog1, char *jog2, int numJogadores){

    printf("\x1b[33m""Digite o nome do jogador 1: ""\x1b[0m");
    getchar();
    fgets(jog1, 64, stdin);
    printf("\n");
    jog1[strlen(jog1) - 1] = '\0';
    if(numJogadores == 1){
        strcpy(jog2, "Computador");
    }
    else{
        printf("\x1b[33m""Digite o nome do jogador 2: ""\x1b[0m");
        fgets(jog2, 64, stdin);
        printf("\n");
        jog2[strlen(jog2) - 1] = '\0';
    }
}

char * pegarComando(int numJog, char *jog1, char *jog2, char mat[][3], int ultimoJog, int * linha, int *coluna, char jog[]){
    
    char comando[64];

    printf("\x1b[33m""\n%s, digite o comando: ""\x1b[0m", jog);
    fgets(comando, 64, stdin);
    
    if(strstr(comando, "marcar")){
        if(strlen(comando) == 10){
            *linha = comando[strlen(comando) - 3] - 48;
            *coluna = comando[strlen(comando) - 2] - 48;
            return "marcar";
        }
        else{
            return "invalido";
        }
    }
    else if(strstr(comando, "voltar")){
        salvarJogo(numJog, jog1, jog2, mat, ultimoJog, "jogoatual.txt");
        return "voltar";
    }
    else if(strstr(comando, "salvar")){
        char str[64];
        for(int i = 0; i < strlen(comando) - strlen("salvar"); i++){
            str[i] = comando[i+7];

        }
        str[strlen(str) - 1] = '\0';
        salvarJogo(numJog, jog1, jog2, mat, ultimoJog, str);
        return "salvar";
    }
    else{
        return "invalido";
    }

}
void arqConfig(Ranking **lista, int *tamLista){
    

    FILE *arquivo = fopen("velha.ini", "r+");

    fscanf(arquivo, "%d ", tamLista);
    
    *lista = alocaLista(*tamLista);
   
    for(int i = 0; i < *tamLista; i++){
        fgets((*lista)[i].nome, 64, arquivo);
        (*lista)[i].nome[strlen((*lista)[i].nome) - 1] = '\0';
        fscanf(arquivo, "%d %d %d ", &(*lista)[i].vitoria, &(*lista)[i].empate, &(*lista)[i].derrota);
    }

    fclose(arquivo);

    ordenaLista(*lista, *tamLista);

}

void ordenaLista(Ranking *lista, int tamLista){

    int vetAux;
    int vetTem;
    Ranking vetTroca;


    for(vetAux = 1; vetAux < tamLista; vetAux++){ // vetAux começa na posição 1 do vetor e vai até a ultima posição;
    
        vetTem = vetAux; // vetTem recebe a posição que está passando no "for";
        
        while (compara(lista[vetTem],lista[vetTem-1])) { // Enquanto o valor que está passando na posição "vetTem" for menor que a posição "vetTem" menos 1, ocorre a troca;
         // Ocorre a troca;
            vetTroca = lista[vetTem];
            lista[vetTem] = lista[vetTem-1];
            lista[vetTem-1] = vetTroca;
            vetTem--; // vetTem decrementa 1;
            if (vetTem == 0) // Quando "vetTem" chegar na posição 0, primeira posição do vetor, o laço while para;
                break;
        }
    }

}

int compara(Ranking a, Ranking b){
    
    if(a.vitoria > b.vitoria){
        return 1;
    }
    else if(a.vitoria == b.vitoria){
        if(a.empate > b.empate){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
}  

void zeraUsuario(Ranking *jog, char *nome){
    
    strcpy((*jog).nome, nome);
    (*jog).vitoria = 0;
    (*jog).empate = 0;
    (*jog).derrota = 0;
}

int buscaJog(Ranking *lista, Ranking jog, int tamLista){

    for(int i = 0; i < tamLista; i++){
        if(!strcmp(jog.nome, lista[i].nome)){
           return i; 
        }
    }
    return -1;
}

Ranking* realocaLista(Ranking **lista, int *tamLista){

    *tamLista = *tamLista + 1;
    Ranking *listaAtt = NULL;
    listaAtt = alocaLista(*tamLista);
    
    if(listaAtt == NULL){
        exit(1);
    }

    for(int i = 0; i < *tamLista - 1; i++){
        listaAtt[i] = (*lista)[i];
    }

    liberaLista(*lista);
    return listaAtt;

}


Ranking* alocaLista(int tamLista){
    Ranking *lista = malloc(tamLista * sizeof(Ranking));
    return lista;
}

void liberaLista(Ranking *lista){
    free(lista);
}

void salvarJogo(int numJog, char *jog1, char *jog2, char mat[][3], int ultimoJog, char *str){
    FILE *arquivo = fopen(str, "w");

    fprintf(arquivo, "%d\n", numJog);
    fprintf(arquivo, "%s\n%s\n", jog1, jog2);
    for(int i = 0 ; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(mat[i][j] != ' '){
            fprintf(arquivo, "%c ", mat[i][j]);
            }else{
                fprintf(arquivo, "- " );
            }
        }
        fprintf(arquivo, "\n");
    }
    fprintf(arquivo, "%d\n", ultimoJog);


    fclose(arquivo);
}

int abrirJogo(int *contaRodadas, int *numJog, char *jog1, char *jog2, char mat[][3], int *ultimoJog, char *str){
    
    FILE *arquivo = fopen(str, "r");

    if(arquivo == NULL){
        return 0;
    }

    fscanf(arquivo, "%d\n", numJog);
    fgets(jog1, 64, arquivo);
    jog1[strlen(jog1) - 1] = '\0';

    fgets(jog2, 64, arquivo);
    jog2[strlen(jog2) - 1] = '\0';    

    for(int i = 0 ; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(mat[i][j] != ' '){
                fscanf(arquivo, "%c ", &mat[i][j]);
            }else{
                fscanf(arquivo, "%c ", &mat[i][j]);
            }
        }
    }
    
    for(int i = 0 ; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(mat[i][j] == '-'){
                mat[i][j] = ' ';
            }
        }
    }

    fscanf(arquivo, "%d\n", ultimoJog);
    fclose(arquivo);

    *contaRodadas = 0;
    for(int i = 0 ; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(mat[i][j] != ' '){
                *contaRodadas += 1;
            }
        }
    }

    return 1;
}

void attArqConfig(Ranking *lista, int tamLista){
    FILE *arquivo = fopen("velha.ini", "w");

    fprintf(arquivo, "%d\n", tamLista);
    
    for(int i = 0; i < tamLista; i++){
        fprintf(arquivo, "%s\n", lista[i].nome);
        fprintf(arquivo, "%d %d %d\n", lista[i].vitoria, lista[i].empate, lista[i].derrota);
    }

    fclose(arquivo);
}

void mostraRanking(Ranking *lista, int tamLista){
    int CPU = 0;
    printf( "\x1b[32m""\n\t\tRanking de jogadores: \n""\x1b[0m");
    for(int i = 0; i < tamLista; i++){
        if(i < 9){
            printf("\x1b[33m""%s\n""\x1b[0m", lista[i].nome);
            printf("V: %d\tE: %d\tD: %d\n", lista[i].vitoria, lista[i].empate, lista[i].derrota);
            printf("\n");
            if(!strcmp(lista[i].nome, "Computador")){
                CPU = 1;
            }
        }
        else{
            if(CPU == 1){
                printf("%s\n", lista[i].nome);
                printf("V: %d\tE: %d\tD: %d\n", lista[i].vitoria, lista[i].empate, lista[i].derrota);
                break;
            }else{
                if(!strcmp(lista[i].nome, "Computador")){
                    printf("%s\n", lista[i].nome);
                    printf("V: %d\tE: %d\tD: %d\n", lista[i].vitoria, lista[i].empate, lista[i].derrota);
                    break;
                }
            }
        }
    }
}

int verificaGanhador(char tipoJogador, char mat[][3]){
if( (mat[0][0] == tipoJogador && mat[0][1] == tipoJogador && mat[0][2] == tipoJogador) ||
    (mat[1][0] == tipoJogador && mat[1][1] == tipoJogador && mat[1][2] == tipoJogador) ||
    (mat[2][0] == tipoJogador && mat[2][1] == tipoJogador && mat[2][2] == tipoJogador) ||
    (mat[0][0] == tipoJogador && mat[1][0] == tipoJogador && mat[2][0] == tipoJogador) ||
    (mat[0][1] == tipoJogador && mat[1][1] == tipoJogador && mat[2][1] == tipoJogador) ||
    (mat[0][2] == tipoJogador && mat[1][2] == tipoJogador && mat[2][2] == tipoJogador) ||
    (mat[0][0] == tipoJogador && mat[1][1] == tipoJogador && mat[2][2] == tipoJogador) ||
    (mat[0][2] == tipoJogador && mat[1][1] == tipoJogador && mat[2][0] == tipoJogador)){
        return 1;
    }
    else{
        return 0;
    }
}


void antiWin(char mat[][3]){

   if((mat[0][0]==mat[0][1])&&mat[0][2]==' '&&mat[0][0]=='O'){
        mat[0][2]= 'O';   
    }else
    if((mat[0][1]==mat[0][2])&&mat[0][0]==' '&&mat[0][1]=='O'){
        mat[0][0]= 'O';
    }else
    if((mat[0][0]==mat[0][2])&&mat[0][1]==' '&&mat[0][0]=='O'){
        mat[0][1]= 'O';
    }else
    if((mat[1][0]==mat[1][1])&&mat[1][2]==' '&&mat[1][0]=='O'){
        mat[1][2]= 'O';
    }else
    if((mat[1][1]==mat[1][2])&&mat[1][0]==' '&&mat[1][1]=='O'){
        mat[1][0]= 'O';
    }else
    if((mat[1][0]==mat[1][2])&&mat[1][1]==' '&&mat[1][0]=='O'){
        mat[1][1]= 'O';
    }else
    if((mat[2][0]==mat[2][1])&&mat[2][2]==' '&&mat[2][0]=='O'){
        mat[2][2]= 'O';
    }else
    if((mat[2][1]==mat[2][2])&&mat[2][0]==' '&&mat[2][1]=='O'){
        mat[2][0]= 'O';
    }else
    if((mat[2][0]==mat[2][2])&&mat[2][1]==' '&&mat[2][0]=='O'){
        mat[2][1]= 'O';
    }else
    if((mat[0][0]==mat[1][0])&&mat[2][0]==' '&&mat[0][0]=='O'){
        mat[2][0]= 'O';
    }else
    if((mat[0][0]==mat[2][0])&&mat[1][0]==' '&&mat[0][0]=='O'){
        mat[1][0]= 'O';
    }else
    if((mat[1][0]==mat[2][0])&&mat[0][0]==' '&&mat[1][0]=='O'){
        mat[0][0]= 'O';
    }else
    if((mat[0][1]==mat[1][1])&&mat[2][1]==' '&&mat[0][1]=='O'){
        mat[2][1]= 'O';
    }else
    if((mat[0][1]==mat[2][1])&&mat[1][1]==' '&&mat[0][1]=='O'){
        mat[1][1]= 'O';
    }else
    if((mat[1][1]==mat[2][1])&&mat[0][1]==' '&&mat[1][1]=='O'){
        mat[0][1]= 'O';
    }else
    if((mat[0][2]==mat[1][2])&&mat[2][2]==' '&&mat[0][2]=='O'){
        mat[2][2]= 'O';
    }else
    if((mat[0][2]==mat[2][2])&&mat[1][2]==' '&&mat[0][2]=='O'){
        mat[1][2]= 'O';
    }else
    if((mat[1][2]==mat[2][2])&&mat[0][2]==' '&&mat[1][2]=='O'){
        mat[0][2]= 'O';
    }else
    if((mat[0][0]==mat[1][1])&&mat[2][2]==' '&&mat[0][0]=='O'){
        mat[2][2]= 'O';
    }else
    if((mat[0][0]==mat[2][2])&&mat[1][1]==' '&&mat[0][0]=='O'){
        mat[1][1]= 'O';
    }else
    if((mat[1][1]==mat[2][2])&&mat[0][0]==' '&&mat[1][1]=='O'){
        mat[0][0]= 'O';
    }else
    if((mat[0][2]==mat[1][1])&&mat[2][0]==' '&&mat[1][1]=='O'){
        mat[2][0]= 'O';
    }else
    if((mat[2][0]==mat[0][2])&&mat[1][1]==' '&&mat[2][0]=='O'){
        mat[1][1]= 'O';
    }else
    if((mat[2][0]==mat[1][1])&&mat[0][2]==' '&&mat[2][0]=='O'){
        mat[0][2]= 'O';
    }else
    if((mat[0][0]==mat[0][1])&&mat[0][2]==' '&&mat[0][0]=='X'){
        mat[0][2]= 'O';
    }else
    if((mat[0][1]==mat[0][2])&&mat[0][0]==' '&&mat[0][1]=='X'){
        mat[0][0]= 'O';
    }else
    if((mat[0][0]==mat[0][2])&&mat[0][1]==' '&&mat[0][0]=='X'){
        mat[0][1]= 'O';
    }else
    if((mat[1][0]==mat[1][1])&&mat[1][2]==' '&&mat[1][0]=='X'){
        mat[1][2]= 'O';
    }else
    if((mat[1][1]==mat[1][2])&&mat[1][0]==' '&&mat[1][1]=='X'){
        mat[1][0]= 'O';
    }else
    if((mat[1][0]==mat[1][2])&&mat[1][1]==' '&&mat[1][0]=='X'){
        mat[1][1]= 'O';
    }else
    if((mat[2][0]==mat[2][1])&&mat[2][2]==' '&&mat[2][0]=='X'){
        mat[2][2]= 'O';
    }else
    if((mat[2][1]==mat[2][2])&&mat[2][0]==' '&&mat[2][1]=='X'){
        mat[2][0]= 'O';
    }else
    if((mat[2][0]==mat[2][2])&&mat[2][1]==' '&&mat[2][0]=='X'){
        mat[2][1]= 'O';
    }else
    if((mat[0][0]==mat[1][0])&&mat[2][0]==' '&&mat[0][0]=='X'){
        mat[2][0]= 'O';
    }else
    if((mat[0][0]==mat[2][0])&&mat[1][0]==' '&&mat[0][0]=='X'){
        mat[1][0]= 'O';
    }else
    if((mat[1][0]==mat[2][0])&&mat[0][0]==' '&&mat[1][0]=='X'){
        mat[0][0]= 'O';
    }else
    if((mat[0][1]==mat[1][1])&&mat[2][1]==' '&&mat[0][1]=='X'){
        mat[2][1]= 'O';
    }else
    if((mat[0][1]==mat[2][1])&&mat[1][1]==' '&&mat[0][1]=='X'){
        mat[1][1]= 'O';
    }else
    if((mat[1][1]==mat[2][1])&&mat[0][1]==' '&&mat[1][1]=='X'){
        mat[0][1]= 'O';
    }else
    if((mat[0][2]==mat[1][2])&&mat[2][2]==' '&&mat[0][2]=='X'){
        mat[2][2]= 'O';
    }else
    if((mat[0][2]==mat[2][2])&&mat[1][2]==' '&&mat[0][2]=='X'){
        mat[1][2]= 'O';
    }else
    if((mat[1][2]==mat[2][2])&&mat[0][2]==' '&&mat[1][2]=='X'){
        mat[0][2]= 'O';
    }else
    if((mat[0][0]==mat[1][1])&&mat[2][2]==' '&&mat[0][0]=='X'){
        mat[2][2]= 'O';
    }else
    if((mat[0][0]==mat[2][2])&&mat[1][1]==' '&&mat[0][0]=='X'){
        mat[1][1]= 'O';
    }else
    if((mat[1][1]==mat[2][2])&&mat[0][0]==' '&&mat[1][1]=='X'){
        mat[0][0]= 'O';
    }else
    if((mat[0][2]==mat[1][1])&&mat[2][0]==' '&&mat[1][1]=='X'){
        mat[2][0]= 'O';
    }else
    if((mat[2][0]==mat[0][2])&&mat[1][1]==' '&&mat[2][0]=='X'){
        mat[1][1]= 'O';
    }else
    if((mat[2][0]==mat[1][1])&&mat[0][2]==' '&&mat[2][0]=='X'){
        mat[0][2]= 'O';
    }else 
    if(mat[1][1]!='X' && mat[1][1] != 'O'){
        mat[1][1] = 'O';
    }
    else 
    if(mat[0][2]!='X' && mat[0][2] !='O'){
        mat[0][2] = 'O';
    }
    else 
    if(mat[2][0] != 'X' && mat[2][0] !='O'){
        mat[2][0] = 'O';
    }
    else 
    if(mat[2][2] != 'X' && mat[2][2] !='O'){
        mat[2][2] = 'O';
    }
    else 
    if(mat[1][0] != 'X' && mat[1][0] !='O'){
        mat[1][0] = 'O';
    }
    else 
    if(mat[0][1]!='X' && mat[0][1] !='O'){
        mat[0][1] = 'O';
    }
    else 
    if(mat[0][0]!='X' && mat[0][0] !='O'){
        mat[0][0] = 'O';
    }
    else 
    if(mat[2][1]!='X' && mat[2][1] !='O'){
        mat[2][1] = 'O';
    }
    else if(mat[1][2]!='X' && mat[1][2] !='O'){
        mat[1][2] = 'O';
    }
     
}




