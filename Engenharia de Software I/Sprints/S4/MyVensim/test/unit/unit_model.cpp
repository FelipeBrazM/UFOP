/* Felipe Braz Marques - 22.1.4030 */

#include <cassert>
#include <iostream>
#include "../../src/System.h"
#include "../../src/Flow.h"
#include "../../src/Model.h"
#include "unit_model.h"

using namespace std;


void run_unit_tests_model() {
    
    unit_model_constructor(); 
    unit_model_destructor(); 

    unit_model_getName(); 
    unit_model_setName(); 

    unit_model_getTime(); 
    unit_model_setTime(); 

    unit_model_add(); 

    unit_model_execute(); 
}

void unit_model_constructor(void) {
    AbstractModel *m1 = new Model();

    assert(m1->getName() == "");
    assert(m1->getTime() == 0.0);

    Model m2("model name", 10.0);

    assert(m2.getName() == "model name");
    assert(m2.getTime() == 10.0);
}

void unit_model_destructor(void) {

}

void unit_model_getName() {
    Model m("model name");

    assert(m.getName() == "model name");
}

void unit_model_setName() {
    Model m;

    m.setName("new model name");

    assert(m.getName() == "new model name");
}

void unit_model_getTime() {
    Model m("model name", 0.0);

    assert(m.getTime() == 0.0);
}

void unit_model_setTime() {
    Model m;

    m.setTime(87.0);

    assert(m.getTime() == 87.0);
}

void unit_model_add() {
    AbstractSystem *s1 = new System();
    AbstractFlow *f1 = new Flow();
    Model m;

    m.add(s1);
    m.add(f1);

    assert(m.getSystensSize() == 1);
    assert(m.getFlowsSize() == 1);

    delete s1;
    delete f1;
}

void unit_model_execute(){
    Model m;

    m.execute(0, 10, 1);

    assert(m.getTime() == 10);
}