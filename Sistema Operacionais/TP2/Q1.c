#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <signal.h>

#define READ 0
#define WRITE 1

void menu();
void VerificCreatePipe(int *, int *);
void VerificOpenPipe(int *);

int main(){

    menu();

    int saldo[2], opcao[2]; 
    int caractere = 0;

    //Verific if able to create a pipeline, in case of sucess return value 0
    VerificCreatePipe(saldo, opcao);

    //Verific if able to open and write in the archive
    VerificOpenPipe(saldo);
   

    pid_t pidDad = getpid(); /* Variable to store the pid of dad process */
    pid_t son1 = fork(); /* Variable to store the pid of son process, the function "fork()" return the pid */
    if(son1 < 0){ /* If have a problem to do "fork()" the function return a value negative */
        printf("\x1b[31m""Failed to fork\n""\x1b[0m");
        exit(1);
    }
    fflush(stdin);

    pid_t son2 = -1;
    if(getpid() == pidDad){
        son2 = fork();
        if(son2 < 0){
            exit(1);
        }
        if(son2 == 0){
            son1 = -1;
        }
    }

    if(getpid() == pidDad){ 
        int x;
        while(caractere != 107 || caractere != 75){ /* While caracter different of 'k' or 'K' the loop work */
            do{ /* Loop to capture characters how do nothing for the code */
                caractere = (int)getchar(); 
            }while((caractere != 43) && (caractere != 83) && (caractere != 115) && (caractere != 107) && (caractere != 75) && (caractere != 45));

            if(caractere == 83 || caractere == 115){ /* if to print the saldo in the terminal */
                read(saldo[READ], &x, sizeof(int));
                printf("\x1b[36m""-----------------------------\n");
                printf("\x1b[33m""Print em PID : %d\n", getpid());
                printf("Saldo        : %d UD\n""\x1b[0m", x);
                printf("\x1b[36m""-----------------------------\n""\x1b[0m");
                write(saldo[WRITE], &x, sizeof(int));
            }
            else{
                write(opcao[WRITE], &caractere, sizeof(int));
            }

            if(caractere == 107 || caractere == 75){ /* if to kill the children */
                printf("\x1b[31m""-----------------------------\n""\x1b[0m");
                kill(son1, SIGKILL);
                kill(son2, SIGKILL);
                kill(getpid(), SIGKILL);
                exit(0);
            }
        }
    }
    else if(son1 == 0){
        int operacao;
        int x;
        do{
            read(opcao[READ], &operacao, sizeof(int));

            if(operacao == 43){
                printf("\x1b[36m""-----------------------------\n""\x1b[0m");
                printf("\x1b[33m""Soma em PID: %d\n""\x1b[0m", getpid());
                printf("\x1b[36m""-----------------------------\n""\x1b[0m");
                read(saldo[READ], &x, sizeof(int));
                x += 500;
                write(saldo[WRITE], &x, sizeof(int));  
            }
            else{
                write(opcao[WRITE], &operacao, sizeof(int));
            }
        }while(operacao != 107 || operacao != 75);
    }
    else if(son2 == 0){
        int operacao; 
        int x;
        do{
            read(opcao[READ], &operacao, sizeof(int));

            if(operacao == 45){
                printf("\x1b[36m""-----------------------------\n""\x1b[0m");
                printf("\x1b[33m""Remove em PID: %d\n", getpid());
                printf("\x1b[36m""-----------------------------\n""\x1b[0m");
                read(saldo[READ], &x, sizeof(int));
                x -= 500;
                write(saldo[WRITE], &x, sizeof(int));
            }
            else{
                write(opcao[WRITE], &operacao, sizeof(int)); 
            }
        }while(operacao != 107 ||operacao != 75);
    }
    else{}
    return 0;
}

void menu(){
    printf("\x1b[32m""\nPara somar 500 UD aperte [+]\n");
    printf("Para subitrair 500 UD aperte [-]\n");
    printf("Para imprimir o saldo aperte [s]\n");
    printf("Para encerrar o programa aperte [k]\n");
    printf("Para confirmar a sua escolha aperte [ENTER]\n\n");
    printf("O valor incial do saldo é: 0.0 UD\n""\x1b[0m");
}

void VerificCreatePipe(int *saldo, int *opcao){
    if(pipe(saldo) < 0 || pipe(opcao) < 0){
        printf("\x1b[31m""Error of create the pipe\n""\x1b[0m");
        exit(1);
    }
}

void VerificOpenPipe(int *saldo){
    int aux = 0;
    if(write(saldo[WRITE], &aux, sizeof(int)) == -1){
        printf("\x1b[31m""Error, not possible write in the pipe\n""\x1b[0m");
    }
}

