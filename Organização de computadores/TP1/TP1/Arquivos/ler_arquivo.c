#include "../estruturas.h"

int main(int argc, char const *argv[])
{
    FILE *arq;
    if ((arq = fopen(argv[1], "rb")) == NULL)
    {
        printf("erro\n");
    }
    TipoRegistro *regs = malloc(atoi(argv[2]) * sizeof(TipoRegistro));

    fread(regs, atoi(argv[2]), sizeof(TipoRegistro), arq);
    for (int i = 0; i < atoi(argv[2]); i++)
    {
        printf("Chave: %ld\n \tValor 1: %ld\n \tValor 2: %s\n \tValor 3: %s\n", regs[i].Chave, regs[i].dado1, regs[i].dado2, regs[i].dado3);
        printf("QTD DE REGISTROS: %d\n", i+1);
    }

    free(regs);
    fclose(arq);

    return 0;
}



