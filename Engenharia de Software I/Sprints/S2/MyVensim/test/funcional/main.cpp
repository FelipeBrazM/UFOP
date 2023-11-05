/* Felipe Braz Marques - 22.1.4030*/
/* Para executar o código vai no diretório onde está o Makefile, da um make. Ao gerar um bin, ele vai para a pasta bin,
    na pasta bin, execute ./funcionalexe
*/
#ifndef MAIN_FUNCIONAL_TESTS
#define MAIN_FUNCIONAL_TESTS

#include "funcional_test.h"
#include "../../src/Model.h"
#include "../../src/System.h"
#include "../../src/Flow.h"

int main(){

    exponentialFuncionalTest();

    logisticalFuncionalTest();

    complexFuncionalTest();

    return 0;
}

#endif