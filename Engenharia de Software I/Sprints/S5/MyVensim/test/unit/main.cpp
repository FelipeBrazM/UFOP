// Felipe Braz Marques - 22.1.4030

#ifndef MAIN_UNIT_TESTS
#define MAIN_UNIT_TESTS

#include "unit_test.h"
#include "../../src/AbstractModel.h"
#include "../../src/AbstractSystem.h"
#include "../../src/AbstractFlow.h"

int main(){

    cout << "Starting unit tests:" << endl;
    unitTest();
    cout << "Unit tests completed successfully" << endl;

    return 0;
}

#endif