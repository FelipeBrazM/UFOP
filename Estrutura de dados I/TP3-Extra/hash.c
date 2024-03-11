#include "hash.h"

#include <stdio.h>
#include <string.h>

int h(Chave chave) {
    float p[] = {0.8326030060567271, 0.3224428884580177, 
                 0.6964223353369197, 0.1966079596929834, 
                 0.8949283476433433, 0.4587297824155836, 
                 0.5100785238948532, 0.05356055934904358, 
                 0.9157270141062215, 0.7278472432221632};
    int tamP = 10;
    
    int i;
    unsigned int soma = 0;
    int comp = strlen(chave);

    for(i = 0; i < comp; i++)
        soma += (unsigned int) chave[i] * p[i % tamP];

    return (soma % M);
}

int pegarChaves(Chave* chaves) {
    int i = 0;
    char* token;
    char str[MAX_STR];
    
    // tokenizacao da string original, divide em strings delimitadas por espaco em branco
    fgets (str, MAX_STR, stdin);
    str[strcspn(str, "\n")] = 0;

    token = strtok(str, " ");

    while (token != NULL) {
        strcpy(chaves[i++], token);
        //inserir o item na lista adequada
        token = strtok(NULL, " ");
    }
    return i;
}

