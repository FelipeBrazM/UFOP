#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <signal.h>

#define NUMTHREADS 3

// Removendo pthread_join acaba com a espera para fechar a threads, fazendo com que a Race Condition apareça

pthread_t threads[NUMTHREADS];
int saldo = 0;
int flag = 0;

void *thread_func_1(void *arg); // imprime
void *thread_func_2(void *arg); // soma
void *thread_func_3(void *arg); // subtracao
void menu();

int main(int argc, char **argv) {
    int i;
    int opcao = 0;
   
    menu();

    while(opcao != 83 && opcao != 115){ // sair
        opcao = (int)getchar();

        if (opcao == 46){ // imprime
            pthread_create(&(threads[0]), NULL, thread_func_1, NULL);
            //Cria thread passando a função de impressao e realiza solicitação do usuario
        }
        else if (opcao == 43){ // soma
            pthread_create(&(threads[1]), NULL, thread_func_2, NULL);
            //pra criar uma nova thread com solicitação do usuario
        }
        else if (opcao == 45){ // subtrai
            pthread_create(&(threads[2]), NULL, thread_func_3, NULL);
        }
        else if (opcao == 83 || opcao == 115){
            pthread_kill(threads[0], 0);
            pthread_kill(threads[1], 0);
            pthread_kill(threads[2], 0);

            printf("------------------------------\n");
            printf("KILLED\n");
            printf("------------------------------\n");
        }
        else{
            continue;
        }
    }

    return 0;
}

void *thread_func_1(void *arg) { // imprime
    pid_t tid;
    tid = syscall(__NR_gettid);
    printf("------------------------------\n");
    printf("TID: %d\n",tid);
    printf("Saldo: %d\n", saldo);
    printf("------------------------------\n");
    pthread_exit(0);
}

void *thread_func_2(void *arg) { // soma
    pid_t tid;
    tid = syscall(__NR_gettid);
    printf("------------------------------\n");
    printf("TID: %d\n",tid);
    saldo += 500;
    printf("------------------------------\n");
    pthread_exit(0);
}

void *thread_func_3(void *arg) { // subtracao
    pid_t tid;
    tid = syscall(__NR_gettid);
    printf("------------------------------\n");
    printf("TID: %d\n",tid);
    saldo -= 500;
    printf("------------------------------\n");
    pthread_exit(0);
}

void menu(){
    printf("\nAperte [+] para somar 500 UD;\n");
    printf("Aperte [-] para subtrair 500 UD;\n");
    printf("Aperte [.] para imprimir o valor do saldo;\n");
    printf("Aperte [s] para destuir todos os threads e finalizar a execucao.\n");
    printf("Aperte [ENTER] para confirmar as operacoes.\n\n");
    printf("O valor inicial de saldo eh: %d\n\n",saldo);
}