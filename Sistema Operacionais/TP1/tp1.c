#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void QuebraLinha(){
    printf("\n");
}

int main(){
    
    char comando[32];
    char matar[32] = "kill -9 ";
    char prioridade[32] = "renice 10 -p ";

    //Exibindo a versão do Ubuntu 
    system("cat /etc/os-release");
    QuebraLinha();

    //Exibindo o arquito TXT com meu nome 
    system("cat felipe.txt");
    QuebraLinha();

    //Executando o comando ps
    system("ps");
    QuebraLinha();

    //Executando o comando pstree
    system("pstree");
    QuebraLinha();
    
    //Executando o comando top
    system("top");
    QuebraLinha();

    //Executando o comando kill
    printf("Entre com o valor do PID que você deseja dar o kill: ");
    scanf("%s", comando);
    strcat(matar,comando);
    system(matar);
    QuebraLinha();
    system("ps");
    
    //Executando o comando killall
    system("killall");
    QuebraLinha();

    //Executando o comando pkill
    system("pkill");
    QuebraLinha();

    //Executando o comando renice
    system("top");
    printf("Entre com o valor do PID que você deseja passar para a prioridade 10: ");
    scanf("%s", comando);
    strcat(prioridade,comando);
    system(prioridade);
    QuebraLinha();
    system("top");

    return 0;
}