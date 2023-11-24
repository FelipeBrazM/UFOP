#include <cassert>
#include <iostream>

#include "unit_test.h"
#include "unit_system.h"
#include "unit_flow.h"
#include "unit_model.h"

using namespace std;

void unitTest(){

    cout << "System test" << endl;
    run_unit_tests_system();
    cout << "OK" << endl;

    cout << "Flow test" << endl;
    run_unit_tests_flow();
    cout << "OK" << endl;
    
    cout << "Model test" << endl;
    run_unit_tests_model();
    cout << "OK" << endl;
}