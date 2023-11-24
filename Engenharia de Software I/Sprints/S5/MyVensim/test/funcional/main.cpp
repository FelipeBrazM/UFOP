#ifndef MAIN_FUNCIONAL_TESTS
#define MAIN_FUNCIONAL_TESTS

#include "funcional_test.h"
#include "../../src/AbstractModel.h"
#include "../../src/AbstractSystem.h"
#include "../../src/AbstractFlow.h"

int main(){

    exponentialFuncionalTest();

    logisticalFuncionalTest();

    complexFuncionalTest();

    return 0;
}

#endif