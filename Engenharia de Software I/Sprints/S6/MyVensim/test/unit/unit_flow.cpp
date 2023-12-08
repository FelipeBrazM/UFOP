#include "unit_flow.h"

class Testflow : public FlowHandlePointer {
    public:
    Testflow(const string name="teste", System* input=NULL, System* output=NULL, double tax=0.0) : FlowHandlePointer(name, input, output,tax) {}
    virtual ~Testflow() {}
    virtual double execute(){
        return 500.0;
    }
};

void run_unit_tests_Flow(void){
    unit_Flow_constructor();
    unit_Flow_destructor();

    unit_Flow_getName();
    unit_Flow_setName();

    unit_Flow_getTax();
    unit_Flow_setTax();

    unit_Flow_getSystemInput();
    unit_Flow_setSystemInput();

    unit_Flow_getSystemOutput();
    unit_Flow_setSystemOutput();

    unit_Flow_execute();

    cout << "Unit Flow Tests complete" << endl;
}

void unit_Flow_constructor(void){
    Flow* f1 = new Testflow();
    assert(f1->getName() == "teste");
    assert(f1->getSystemInput() == NULL);
    assert(f1->getSystemOutput() == NULL);
    assert(f1->getTax() == 0.0);

    System* sys1 = NULL, *sys2 = NULL;
    Flow* f2 = new Testflow("TestName", sys1, sys2, 0.0);
    assert(f2->getName() == "TestName");
    assert(f2->getSystemInput() == sys1);
    assert(f2->getSystemOutput() == sys2);
    assert(f2->getTax()==0.0);

    delete f1; delete f2;
    delete sys1; delete sys2;
}
void unit_Flow_destructor(void){
}

void unit_Flow_getName(void){
    Flow* f1 = new Testflow("TestName");
    assert(f1->getName() == "TestName");

    delete f1;
}
void unit_Flow_setName(void){
    Flow* f1 = new Testflow();

    f1->setName("NewName");

    assert(f1->getName() == "NewName");

    delete f1;
}

void unit_Flow_getTax(void){
    Flow* f1 = new Testflow();
    assert(f1->getTax() == 0.0);

    delete f1;
}
void unit_Flow_setTax(void){
    Flow* f1 = new Testflow();
    f1->setTax(50.0);

    assert(f1->getTax() == 50.0);

    delete f1;
}

void unit_Flow_getSystemInput(void){
    System* s1 = NULL;
    Flow* f1 = new Testflow("test", s1, NULL);
    assert(f1->getSystemInput() == s1);

    delete f1;
    delete s1;

}
void unit_Flow_setSystemInput(void){
    System* s1 = NULL;
    Flow* f1 = new Testflow();

    f1->setSystemInput(s1);

    assert(f1->getSystemInput() == s1);

    delete s1;
    delete f1;
}

void unit_Flow_getSystemOutput(void){
    System* s1 = NULL;
    Flow* f1 = new Testflow("test", NULL, s1);
    assert(f1->getSystemOutput() == s1);

    delete f1;
    delete s1;
}
void unit_Flow_setSystemOutput(void){
    System* s1 = NULL;
    Flow* f1 = new Testflow();

    f1->setSystemOutput(s1);

    assert(f1->getSystemOutput() == s1);

    delete s1;
    delete f1;
}

void unit_Flow_execute(void){
    Flow* f1 = new Testflow();

    assert(f1->execute() - 50.0 == 450.00);

    delete f1;
}

