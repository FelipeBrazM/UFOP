#include "../abp.h"

int main(int argc, char const *argv[]){

    FILE *arq = fopen(argv[1], "rb");
    if(arq == NULL) 
    {
        printf("Erro ao abrir arquivo\n"); return 0;
    }
    TipoItem item;

    while((fread(&item, sizeof(TipoItem), 1, arq) != 0))
    {
        printf("esq: %ld chave: %ld dir: %ld\n", item.esq, item.item.Chave, item.dir);  
    }
    
    fclose(arq);
    return 0;

}
