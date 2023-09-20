//Felipe Braz Marques 22.1.4030

#include "function.h"

 
int main(){

    
    
    //Inicialização das variáveis.
    int flag, numJogadores, linha, coluna, vezDeQuem, tamLista, verificaEmpate;
    char mat[3][3];
    char op;
    char jog1[64], jog2[64];
    char comando[64]; 
    char jogoSalvo[64];
    Ranking *lista = NULL;
    Ranking jogador1;
    Ranking jogador2;
    
    //Leitura do arquivo de configuração.
    arqConfig(&lista, &tamLista);

    while(1){
        
        flag = 1;
        vezDeQuem = 1;
        verificaEmpate = 0;

        while(flag){

            //Essa função printa todo o menu principal.
            menuPrincipal();
            
            printf("\x1b[36m""Escolha a opção: ""\x1b[0m");
            scanf("%c", &op);
       
            switch(op){

                //  O case 0, atualiza o arquivo de configuração e fecha o jogo.   
                case '0':

                    attArqConfig(lista, tamLista);
                    liberaLista(lista);
                    return 0;
                    break;

                //  O case 1, começa um jogo novo.
                case '1':         

                    printf("\x1b[33m""\nDigite o número de jogadores (1 ou 2): ""\x1b[0m");
                    scanf("%d", &numJogadores);
                    printf("\n");
                    
                    //Essa função coleta os nomes dos jogadores.
                    pegaJogadores(jog1, jog2, numJogadores);

                    //Essas funções zeram as structs que armazenam os dados de ambos jogadores.
                    zeraUsuario(&jogador1, jog1);
                    zeraUsuario(&jogador2, jog2);

                    //Essa função inicializa toda a matriz com ' '.
                    inicializarMatriz(mat);              

                    //Essa função printa todo o tabuleiro.
                    printaMatriz(mat);
                    
                    flag = 0;
                    break;

                // O case 2, abre um jogo salvo em disco.
                case '2':
                    printf("\x1b[36m""\nDigite o nome do arquivo que deseja abrir: ""\x1b[0m");
                    getchar();

                    fgets(jogoSalvo, 64, stdin);
                    jogoSalvo[strlen(jogoSalvo) - 1] = '\0';

                    /*  Essa função abre o jogo que está salvo no disco.
                        Se não for possível abrir o arquivo, aparece uma mensagem de erro, e manda 
                        o usuário para o menu principal.
                    */
                    if(abrirJogo(&verificaEmpate, &numJogadores, jog1, jog2, mat, &vezDeQuem, jogoSalvo)){
                        printf("\n\n\n");
                        printf( "\x1b[32m""Bem vindo de volta, pronto para vencer!?\n""\x1b[0m");
                        printaMatriz(mat);
                        flag = 0;
                    }
                    else{
                        printf("\x1b[31m""\nEste arquivo não existe!\n""\x1b[0m");
                        printf("\x1b[36m""Confira o nome do arquivo que deseja abrir.\n""\x1b[0m");
                        continue;
                    }
                    zeraUsuario(&jogador1, jog1);
                    zeraUsuario(&jogador2, jog2);
                    break;

                // O case 3, continua o jogo que a pessoa estava jogando quando digitou o comando "Voltar".
                case '3':

                    /* Essa função (abrirJogo) abre o jogo da sessão atual, quando a pessoa apertar voltar.
                        Se não for possível abrir o arquivo, aparece uma mensagem de erro, e manda 
                        o usuário para o menu principal.
                    */ 
                    if(abrirJogo(&verificaEmpate, &numJogadores, jog1, jog2, mat, &vezDeQuem, "jogoatual.txt")){
                        printf("\n\n\n");
                        getchar();
                        printaMatriz(mat);
                        flag = 0;
                    }
                    else{
                        printf("\x1b[31m""\nEste arquivo não existe!\n""\x1b[0m");
                        printf("\x1b[36m""Para usar essa opção, é necessário ter salvado pelo menos uma vez!\n""\x1b[0m");
                        continue;
                    }
                    zeraUsuario(&jogador1, jog1);
                    zeraUsuario(&jogador2, jog2);
                    break;

                //  O case 4, mostra o ranking.
                case '4': 

                    mostraRanking(lista, tamLista);
                    getchar();
                    printf("\x1b[35m""\nDigite qualquer tecla para voltar ao menu inicial!\n""\x1b[0m");
                    char lixo;
                    scanf("%c", &lixo);

                    flag = 1;
                    break;

                default: 
                    printf("\x1b[31m""\nOpção inválida! Tente novamente\n""\x1b[0m");

            }
        }

        // Aqui é onde o jogo acontece.
        while(1){
            if(numJogadores == 2){
                        
                    /* Essa variável "vezDeQuem", me ajuda a controlar caso algum dos dois usuários digite um comando inválido.
                    Ela é inicializada fora desse while com o valor de (1), que é o necessário para entrar no primeiro if para o jogador 1.
                    Quando o jogador 1 termina de passar o comando que ele deseja, a variável passa a valer (2).
                    Que é o valor necessário para entrar no if para o jogador 2 jogar.
                    Se um deles digitar "voltar", a variável recebe o valor de 3, e tem um continue, voltando ao início e entra no if, que dentro
                    dele tem um break, fazendo com que assim ele volte ao menu principal. 
                    */

                    while(1){
                        
                        /*  A variável (verificaEmpate), é incrementada a cada vez que algum jogador marca.
                            Quando chega a nove jogadas, caracteriza empate. Aparece a mensagem de empate.
                            E manda o usuário para o menu principal.    */

                        if(verificaEmpate == 9){
                            printf("\x1b[31m""\nDeu velha!\n");
                            printf("\nDigite qualquer tecla para continuar!\n""\x1b[0m");
                            jogador1.empate++;
                            jogador2.empate++;
                            char lixo2;
                            scanf("%c", &lixo2);
                            break;
                        }

                        else if(vezDeQuem == 1){
                            
                            /* Essa função copia o comando que a função pegar comando recebe, para realizar o que cada comando pede,
                                Se for diferente de marcar, voltar ou salvar, ele volta para o início onde pega o comando, e solicita novamente.
                                E se a coordenada que o usuário passou for maior que a matriz suporta, ou já estiver ocupada, também solicita que 
                                ele tente novamente. 
                            */

                            strcpy(comando, pegarComando(numJogadores, jog1, jog2, mat, vezDeQuem, &linha, &coluna, jog1));

                            if(!strcmp("marcar", comando)){

                                if((linha > 3) || (coluna > 3) || (linha < 1) || (coluna < 1)){
                                    printf("\x1b[31m""\nCoordenadas inválidas.\nTente novemente!\n""\x1b[0m");
                                    continue;
                                }
                                if(mat[linha-1][coluna-1] == 'X'|| mat[linha-1][coluna-1] == 'O'){
                                    printf("\x1b[31m""Posição desejada já está ocupada!\n:(\nTente novamente!\n""\x1b[0m");
                                    continue;
                                }

                                mat[linha-1][coluna-1] = 'X';
                                verificaEmpate++;
                                printaMatriz(mat);

                                /*  Essa função percorre a matriz inteira vendo se o jogador ganhou. Se em alguma linha, coluna ou diagonal tiver,
                                    preenchida por 'X' ou por 'O', ela encerra o jogo atual. Mostrando o ganhador. Existe também duas structs auxiliares,
                                    elas foram inicializadas com 0, e dependendo de quem ganhou ou quem perdeu, ou se der empate elas são incrementadas,
                                    para no final do código atualizar o ranking. 
                                */

                                if(verificaGanhador('X', mat)){
                                    printf("\x1b[35m""\n\nParabén %s, você ganhou!\n", jog1);
                                    printf("Digite qualquer tecla para continuar!\n""\x1b[0m");
                                    jogador1.vitoria++;
                                    jogador2.derrota++;
                                    char lixo;
                                    scanf("%c", &lixo);
                                    vezDeQuem = 3;
                                    break;
                                }
                            }
                            else if(!strcmp("salvar", comando)){ 
                                printf("\x1b[32m""Jogo salvo com sucesso!\n""\x1b[0m");
                                continue;
            
                            }
                            else if(!strcmp("voltar", comando)){
                                vezDeQuem = 3;
                                break;
                            }
                            else if(!strcmp("invalido", comando)){
                                printf("\x1b[31m""Comando inválido, tente novamente!\n""\x1b[0m");
                                continue;
                            }
                        vezDeQuem = 2;
                    }
                
                
                    //Pega comando para o jogador 2 
                        
                        else if(vezDeQuem == 2){   
                            strcpy(comando, pegarComando(numJogadores, jog1, jog2, mat, vezDeQuem, &linha, &coluna, jog2));

                            if(!strcmp("marcar", comando)){
                            
                                if((linha > 3) || (coluna > 3) || (linha < 1) || (coluna < 1)){
                                    printf("\x1b[31m""Coordenadas inválidas\n""\x1b[0m");
                                    continue;
                                }
                                if(mat[linha-1][coluna-1] == 'X'|| mat[linha-1][coluna-1] == 'O'){
                                    printf("\x1b[31m""\nPosição desejada já está ocupada!\n:(\nTente novamente!\n""\x1b[0m");
                                    continue;
                                }

                                mat[linha-1][coluna-1] = 'O';
                                verificaEmpate++;
                                printaMatriz(mat);

                                if(verificaGanhador('O', mat)){
                                    printf("\x1b[35m""\n\nParabén %s, você ganhou!\n", jog2);
                                    printf("Digite qualquer tecla para continuar!\n""\x1b[0m");
                                    jogador2.vitoria++;
                                    jogador1.derrota++;
                                    char lixo;
                                    scanf("%c", &lixo);
                                    vezDeQuem = 3;
                                    break;
                                }
                                        
                            }

                            else if(!strcmp("salvar", comando)){
                                printf("\x1b[32m""Jogo salvo com sucesso!\n""\x1b[0m");
                                break;                
                            }
                            else if(!strcmp("voltar", comando)){
                                vezDeQuem = 3;
                                break;
                            }
                            else if(!strcmp("invalido", comando)){
                                printf("\x1b[31m""\nComando inválido, tente novamente!\n""\x1b[0m");
                                continue;
                            }
                            vezDeQuem = 1;
                        }   
                    
                    }
                    if(vezDeQuem == 3){
                        break;
                    }
                }

                if(numJogadores == 1){
                    
                    int voltar = 1;

                    while(1){
                        if(verificaEmpate == 9){
                            printf("\x1b[31m""\nDeu velha!\n");
                            printf("\nDigite qualquer tecla para continuar!\n""\x1b[0m");
                            jogador1.empate++;
                            jogador2.empate++;
                            voltar = 2;
                            char lixo2;
                            scanf("%c", &lixo2);
                            break;
                        }
                        strcpy(comando, pegarComando(numJogadores, jog1, jog2, mat, 1, &linha, &coluna, jog1));

                        if(!strcmp("marcar", comando)){

                            if((linha > 3) || (coluna > 3) || (linha < 1) || (coluna < 1)){
                                printf("\x1b[31m""\nCoordenadas inválidas.\nTente novemente!\n""\x1b[0m");
                                continue;
                            }
                            if(mat[linha-1][coluna-1] == 'X'|| mat[linha-1][coluna-1] == 'O'){
                                printf("\x1b[31m""\nPosição desejada já está ocupada!\n:(\nTente novamente!\n""\x1b[0m");
                                continue;
                            }

                            mat[linha-1][coluna-1] = 'X';
                            verificaEmpate++;
                            printaMatriz(mat);

                            if(verificaEmpate == 9){
                                printf("\x1b[31m""\nDeu velha!\n");
                                printf("\nDigite qualquer tecla para continuar!\n""\x1b[0m");
                                jogador1.empate++;
                                jogador2.empate++;
                                voltar = 2;
                                char lixo2;
                                scanf("%c", &lixo2);
                                voltar = 2;
                                break;
                            }

                            if(verificaGanhador('X', mat)){
                                printf("\x1b[35m""\n\nParabén %s, você ganhou!\n", jog1);
                                printf("Digite qualquer tecla para continuar!\n""\x1b[0m");
                                jogador1.vitoria++;
                                jogador2.derrota++;
                                char lixo;
                                scanf("%c", &lixo);
                                voltar = 2;
                                break;
                            }
                        }
                        else if(!strcmp("salvar", comando)){ 
                            printf("\x1b[32m""Jogo salvo com sucesso!\n""\x1b[0m");
                            continue;
                        }
                        else if(!strcmp("voltar", comando)){
                            voltar = 2;
                            break;
                        }
                        else if(!strcmp("invalido", comando)){
                            printf("\x1b[31m""\nComando inválido, tente novamente!\n""\x1b[0m");
                            continue;
                        }
                    
                    // Jogada do computador

                    /*  Para fazer a IA do meu jogo da velha, eu basicamente fiz uma cadeia de "if else", primeiro ela analisa se pode vencer.
                        Por exemplo:  
                        if((mat[0][0]==mat[0][1])&&mat[0][2]==' '&&mat[0][0]=='O'){
                            mat[0][2]= 'O';
                        } 
                        Nesse caso descrito acima, se na posição 00 e 01 da matriz estiver marcado 'O', e a posição 02 estiver livre, ela vai marcar, 
                        e vencer. Um if-else para cada linha, coluna e diagonal, analisando assim todas as possibilidades.

                        Depois ela analisa se o oponente pode perder, se sim ela vai bloquear a jogada do adversário. 
                        Por exemplo:
                        else if((mat[0][1]==mat[0][2])&&mat[0][0]==' '&&mat[0][1]=='X'){
                                mat[0][0]= 'O';
                        }
                        No código exemplificado, as posições 01 e 02 estão marcadas com 'X', e a posição 00 está livre para ser marcada, se o computador
                        não marcar no 00, o adversário terá uma chance clara de vencer na próxima jogada dele. Então ele marcará essa posição.

                        E quando está no início do jogo, onde nenhum dos casos acima é aplicável, o computador buscará as melhores posições, se o meio estiver
                        livre ele marcará lá, se a primeira jogada do oponente for no meio, ele começara pelas bordas.
                        Por exemplo:
                        else if(mat[1][1]!='X' && mat[1][1] != 'O'){
                                mat[1][1] = 'O';
                        }
                        No modelo mostrado acima, se a posição central da matriz 11, estiver livre a IA, irá marcar nela, pois é uma posição extremamente forte.
                    */
                        antiWin(mat);
                        verificaEmpate++;
                        printf("\n\n");
                        printaMatriz(mat);
                        
                        if(verificaGanhador('O', mat)){
                            printf("\x1b[31m""\n\nQue pena o %s ganhou de você!\n", jog2);
                            printf("Treine um pouco mais. :(\n\n");
                            printf("Digite qualquer tecla para continuar!\n""\x1b[0m");
                            jogador2.vitoria++;
                            jogador1.derrota++;
                            char lixo;
                            scanf("%c", &lixo);
                            voltar = 2;
                            break;
                        }
                    }
                    if(voltar == 2){
                        break;
                    }
                }
            

            break;
        }

        /*  A função (buscaJog), percorre toda a struct de lista buscando se o nome do jogador já existe. Se encontrar retorna a posição (i),
            e atualiza o jogador. Se não for encontrado, é adicionado uma posição na minha struct, como ela está alocada dinamicamente, eu uso a função
            (realocaLista) para fazer isso, esta função usa uma struct auxiliar para armazenar o valor da antiga struct mais uma posição. Posição essa que 
            o último jogador entrará. Libera a antiga lista, e retorna a lista atualizada. O processo é repetido duas vezes (uma para cada jogador).
        */

        int posicao = buscaJog(lista, jogador1, tamLista);    

        if(posicao != -1){
            lista[posicao].vitoria += jogador1.vitoria;
            lista[posicao].empate += jogador1.empate;
            lista[posicao].derrota += jogador1.derrota;
          
        }
        else{
            lista = realocaLista(&lista, &tamLista);
            lista[tamLista -1] = jogador1;
        }

        posicao = buscaJog(lista, jogador2, tamLista);    

        if(posicao != -1){
            lista[posicao].vitoria += jogador2.vitoria;
            lista[posicao].empate += jogador2.empate;
            lista[posicao].derrota += jogador2.derrota;
        }
        else{
            lista = realocaLista(&lista, &tamLista);
            lista[tamLista -1] = jogador2;
        }

        /*  Como pode ter sido adicionado até dois jogadores na minha lista, e eles entraram no final dela, é preciso ordenar de novo a minha struct.
            Essa função desempenha justamente esse papel.
        */
        ordenaLista(lista, tamLista);

        mostraRanking(lista, tamLista);
        printf("\x1b[35m""\nDigite qualquer tecla para voltar ao menu inicial!\n""\x1b[0m");
        char lixo;
        scanf("%c", &lixo);

        continue;
    
    }
    return 0;
}

