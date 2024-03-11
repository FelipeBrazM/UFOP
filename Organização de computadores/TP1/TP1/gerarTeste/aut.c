#include <stdlib.h>
#include <stdio.h>
int main(){
    printf("TM Pré Processamento\n");
    printf("TM Pesquisa\n");
    printf("TM Total\n");
    printf("Trans Média Pré Processamento\n");
    printf("Trans Média Pesquisa\n");
    printf("Trans Média Total\n");
    printf("Comp Pré Processamento\n");
    printf("Comp Média\n");
    printf("Comp Total\n");

    system("./exe 1 100 1 -a");
    system("./exe 2 100 1 -a");
    system("./exe 3 100 1 -a");
    system("./exe 4 100 1 -a");
}