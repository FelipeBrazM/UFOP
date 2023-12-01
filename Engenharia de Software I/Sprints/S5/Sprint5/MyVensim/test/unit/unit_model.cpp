#include "unit_model.h"

class Testflow : public FlowImpl {
    public:
    Testflow(const string name="teste", System* input=NULL, System* output=NULL, double tax=0.0) : FlowImpl(name, input, output,tax) {}
    virtual ~Testflow() {}
    virtual double execute(){
        return 500.0;
    }
};

void run_unit_tests_Model(){

    unit_Model_constructor();
    unit_Model_destructor();

    unit_Model_getName();
    unit_Model_setName();

    unit_Model_getTimeInitial();
    unit_Model_setTimeInitial();

    unit_Model_getTimeFinal();
    unit_Model_setTimeFinal();

    unit_Model_setTime();

    unit_Model_add();
    unit_Model_removal();

    // unit_Model_systemBegin();

    unit_Model_execute();

    cout << "Unit Model Tests complete" << endl;
}

void unit_Model_constructor(void){
    Model *m1 = Model::createModel();
    assert(m1->getName() == "NoName");
    assert(m1->getTimeInitial() == 0.0);
    assert(m1->getTimeFinal() == 0.0);

    Model *m2 = Model::createModel("TesteName", 10.0, 50.0);
    assert(m2->getName() == "TesteName");
    assert(m2->getTimeInitial() == 10.0);
    assert(m2->getTimeFinal() == 50.0);

    delete m1;
    delete m2;

}
void unit_Model_destructor(void){
}

void unit_Model_getName(void){
    Model *m1 = Model::createModel();

    assert(m1->getName() == "NoName");

    delete m1;
}
void unit_Model_setName(void){
    Model *m1 = Model::createModel();
    m1->setName("NewName");

    assert(m1->getName() == "NewName");

    delete m1;
}

void unit_Model_getTimeInitial(void){
    Model *m1 = Model::createModel("Teste", 10.1, 14.0);
    assert(m1->getTimeInitial() == 10.1);

    delete m1;
}
void unit_Model_setTimeInitial(void){
    Model *m1 = Model::createModel("Teste",0.0, 15.6);
    m1->setTimeInitial(10.1);

    assert(m1->getTimeInitial() == 10.1);

    delete m1;
}

void unit_Model_getTimeFinal(void){
    Model *m1 = Model::createModel("Teste", 10.1, 14.0);
    assert(m1->getTimeFinal() == 14.0);

    delete m1;
}
void unit_Model_setTimeFinal(void){
    Model *m1 = Model::createModel("Teste",0.0, 15.6);
    m1->setTimeFinal(20.0);

    assert(m1->getTimeFinal() == 20.0);

    delete m1;
}


void unit_Model_setTime(void){
    Model *m1 = Model::createModel("Teste", 0.0, 100.0);
    m1->setTime(50.0);

    assert(m1->getTime() == 50.0);

    delete m1;
}

void unit_Model_add(void){
    Model *m1 = Model::createModel();
    System* s1 = m1->createSystem();
    m1->createFlow<Testflow>();


    assert((find(m1->systemBegin(), m1->systemEnd(), s1)) != m1->systemEnd());

    delete m1;
}
void unit_Model_removal(void){
    Model *m1 = Model::createModel();
    System *s1 = m1->createSystem();
    m1->createFlow<Testflow>();

    m1->removal(s1);

    assert(!((find(m1->systemBegin(), m1->systemEnd(), s1)) != m1->systemEnd()));

    delete m1;
}

// void unit_Model_systemBegin(void){
//     Model* m1 = Model::createModel();
//     System* s1 = m1->createSystem(), *s2 = m1->createSystem();

//     assert(*(m1->systemBegin()) == s1);

//     Model::deleteModel(m1);
// }


void unit_Model_execute(void){
    Model *m1 = Model::createModel();

    m1->execute(0.0, 0.0);
    assert(fabs(m1->getTime() - 0.0) < 0.0001);

    m1->execute(100.0, 0.0);
    assert(fabs(m1->getTime() - 100.0) < 0.0001);

    delete m1;
}