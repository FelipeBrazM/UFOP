#include <cassert>

#include "../../src/System.h"
#include "unit_system.h"

void run_unit_tests_system(void) {
    unit_system_constructor();
    unit_system_destructor();

    unit_system_getName();
    unit_system_setName();

    unit_system_getValue();
    unit_system_setValue();
}

void unit_system_constructor(){
    
    AbstractSystem *system1 = new System();

    assert(system1->getName() == "");
    assert(system1->getValue() == 0.0);

    System system2(10.0, "system name");

    assert(system2.getName() == "system name");
    assert(system2.getValue() == 10.0);
}

void unit_system_destructor(void) {

}

void unit_system_getName(void) {
    System system(0, "system name");

    assert(system.getName() == "system name");
}

void unit_system_setName(void) {
    System system(0, "system name");

    system.setName("new system name");

    assert(system.getName() == "new system name");
}

void unit_system_getValue(void) {
    System system(10.0, "system name");

    assert(system.getValue() == 10.0);
}

void unit_system_setValue(void) {
    System system(0,"");

    system.setValue(10.0);

    assert(system.getValue() == 10.0);
}