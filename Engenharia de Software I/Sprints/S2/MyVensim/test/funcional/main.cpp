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