// Felipe Braz Marques - 22.1.4030

#include <cassert>
#include "../../src/System.h"
#include "../../src/Flow.h"
#include "unit_flow.h"

void run_unit_tests_flow() {
    unit_flow_constructor();
    unit_flow_destructor();

    unit_flow_getName();
    unit_flow_setName();

    unit_flow_getValue();
    unit_flow_setValue();

    unit_flow_getOrigin();
    unit_flow_setOrigin();

    unit_flow_getDestiny();
    unit_flow_setDestiny();

    unit_flow_execute();
}

double test(AbstractSystem* test1, AbstractSystem* test2){
    return 1;
}

void unit_flow_constructor(void) {

    AbstractFlow* f1 = new Flow();

    assert(f1->getName() == "");
    assert(f1->getOrigin() == NULL);
    assert(f1->getDestiny() == NULL);

    delete f1;

    AbstractSystem *s1 = new System();
    AbstractSystem *s2 = new System();

    Flow f2(s1, s2, test, "flow name");

    assert(f2.getName() == "flow name");
    assert(f2.getOrigin() == s1);
    assert(f2.getDestiny() == s2);

    delete s1;
    delete s2;
}

void unit_flow_destructor(void) {
    
}

void unit_flow_getName() {
    AbstractFlow* f = new Flow(NULL, NULL, test, "flow name");

    assert(f->getName() == "flow name");

    delete f;
}

void unit_flow_setName() {
    AbstractFlow* f = new Flow(NULL, NULL, test, "flow name");

    f->setName("new flow name");

    assert(f->getName() == "new flow name");

    delete f;
}

void unit_flow_getValue() {
    AbstractFlow* f = new Flow();

    assert(f->getValue() == 0.0);

    delete f;
}

void unit_flow_setValue() {
    AbstractFlow* f = new Flow();

    f->setValue(15.6);

    assert(f->getValue() == 15.6);

    delete f;
}

void unit_flow_getOrigin() {
    AbstractSystem *s1 = new System();
    AbstractFlow* f = new Flow(s1, NULL, test, "flow name");

    assert(f->getOrigin() == s1);

    delete s1;
    delete f;
}

void unit_flow_setOrigin() {
    System *s1 = new System();
    AbstractFlow* f = new Flow();

    f->setOrigin(s1);

    assert(f->getOrigin() == s1);

    delete s1;
    delete f;
}

void unit_flow_getDestiny() {
    System *s1 = new System();
    AbstractFlow *f = new Flow(NULL, s1, test, "flow name");

    assert(f->getDestiny() == s1);

    delete s1;
    delete f;
}

void unit_flow_setDestiny() {
    AbstractSystem *s1 = new System();
    AbstractFlow *f = new Flow();

    f->setDestiny(s1);

    assert(f->getDestiny() == s1);

    delete s1;
    delete f;
}

void unit_flow_execute() { //TODO: conferir isso daqui
    AbstractFlow * f = new Flow(NULL, NULL, test, "flow name");

    f->execute();

    assert(f->getValue() == 1);

    delete f;
}