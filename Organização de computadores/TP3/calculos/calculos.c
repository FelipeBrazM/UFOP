#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
    char metodo[20];
    int hit[5];//L1, L2, L3, RAM, Disco respectivamente
    int miss[4];//L1, L2, L3, RAM respectivamente
    int cost;
}Info;

/*
Arquivo .in

Numero de execucoes
Metodo
Hit L1, Miss L1, Hit L2, Miss L2, Hit L3, Miss L3, Hit Ram, Miss Ram, Hit disco, custo
*/

int main(){

    int n;
    scanf("%d", &n);

    Info * infos = malloc(n * sizeof(Info));

    for(int i = 0; i < n; i++){

        scanf("%s", infos[i].metodo);

        //Hits e Miss  L1, L2, L3, RAM 
        for(int j = 0; j < 4; j++)
            scanf("%d%d", &infos[i].hit[j], &infos[i].miss[j]);

        //Hit no disco
        scanf("%d", &infos[i].hit[4]);

        scanf("%d", &infos[i].cost);
    
    }

    for(int i = 0; i < n; i++){
        
        double somaHit[] = {0,0,0,0};

        for(int j = 0; j < 4; j++)
            somaHit[j] = ((double) infos[i].hit[j] / (infos[i].hit[j] + infos[i].miss[j])) * 100;
        
        printf("%s & %.2f\\%% & %.2f\\%% & %.2f\\%% & %.2f\\%% & %.2d & %d \\\\ \\hline", infos[i].metodo, somaHit[0], somaHit[1], somaHit[2], somaHit[3], infos[i].hit[4] ,infos[i].cost);

        printf("\n");
    }


    return 0;
}