#include "indiceInvertido.h"

int main() {

    IndiceInvertido indiceInvertido;
    int nDocumentos;

    inicia(&indiceInvertido);

    leEntrada(&indiceInvertido, &nDocumentos);
    
    leOpcao(&indiceInvertido, nDocumentos);

    liberaListas(&indiceInvertido);

    return 0;
}
