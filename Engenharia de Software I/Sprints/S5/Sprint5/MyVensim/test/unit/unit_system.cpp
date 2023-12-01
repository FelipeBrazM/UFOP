#include "unit_system.h"


void unit_System_constructor(void) {
    System *s1 = new SystemImpl();
    assert(s1->getName() == "NoName");
    assert(s1->getValue() == 0.0);

    System *s2 = new SystemImpl("TestName", 100.0);
    assert(s2->getName() == "TestName");
    assert(s2->getValue() == 100.0);

    delete s1;
    delete s2;
}

void unit_System_destructor(void) {

}

void unit_System_getName(void) {
    System *s1 = new SystemImpl("TestName", 0.0);

    assert(s1->getName() == "TestName");

    delete s1;
}

void unit_System_setName(void) {
    System *s1 = new SystemImpl();

    s1->setName("NewName");

    assert(s1->getName() == "NewName");

    delete s1;
}

void unit_System_getValue(void) {
    System *s1 = new SystemImpl("TestName", 10.0);

    assert(s1->getValue() == 10.0);

    delete s1;
}

void unit_System_setValue(void) {
    System *s1 = new SystemImpl();

    s1->setValue(10.0);

    assert(s1->getValue() == 10.0);

    delete s1;
}

void run_unit_tests_System(){
    unit_System_constructor();
    unit_System_destructor();

    unit_System_getName();
    unit_System_setName();

    unit_System_getValue();
    unit_System_setValue();

    cout << "Unit System tests complete." << endl;
}