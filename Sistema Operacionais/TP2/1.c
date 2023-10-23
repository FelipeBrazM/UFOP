#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <signal.h>

#define LER 0
#define ESCREVER 1

void menu();

int main(){

    menu();



    return 0;
}

void menu(){
    printf("\nPara somar 1000 UD aperte [+]\n");
    printf("Para subitrair 1000 UD aperte [-]\n");
    printf("Para imprimir o saldo aperte [s]\n");
    printf("Para encerrar o programa aperte [k]\n");
    printf("Para confirmar a sua escolha aperte [ENTER]\n\n");
    printf("O valor incial do saldo é: 0.0 UD\n");
}