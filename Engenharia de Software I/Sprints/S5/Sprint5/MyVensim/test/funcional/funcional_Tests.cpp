#include "flows.h"
#include "funcional_Tests.h"

using namespace std;


void ExponentialFunction(){

    Model* model2= Model::createModel("m1", 0.0, 100);
    System* pop1 = model2->createSystem("pop1",100);
    System* pop2 = model2->createSystem("pop2",0);
    model2->createFlow<Exponential>("exponential", pop1, pop2);
    
    model2->execute(0.0, 100.0);

    assert(fabs(round((pop1->getValue() - 36.6032)*10000)) < 1);
    assert(fabs(round((pop2->getValue() - 63.3968)*10000)) < 1);

    printf("Passou teste Exponential function\n");
}

void LogisticFunction(){

    Model *model = Model::createModel("m1", 0.0, 0.0);
    System *p1 = model->createSystem("p1",100);
    System *p2 = model->createSystem("p2",10);
    model->createFlow<Logistic>("logistic",p1,p2);

    model->execute(0.0, 100.0);

    assert(fabs(round((p1->getValue() - 88.2167)*10000)) < 1);
    assert(fabs(round((p2->getValue() - 21.7833)*10000)) < 1);

    printf("Passou teste Logistic function\n");
}

void ComplexFunction(){

    Model* model = Model::createModel("model", 0.0, 0.0);
    System* q1 = model->createSystem("q1", 100);
    System* q2 = model->createSystem("q2", 0);
    System* q3 = model->createSystem("q3", 100);
    System* q4 = model->createSystem("q4", 0);
    System* q5 = model->createSystem("q5", 0);
    model->createFlow<ComplexFlow>("v", q4, q1);
    model->createFlow<ComplexFlow>("u", q3, q4);
    model->createFlow<ComplexFlow>("g", q1, q3);
    model->createFlow<ComplexFlow>("f", q1, q2);
    model->createFlow<ComplexFlow>("r", q2, q5);
    model->createFlow<ComplexFlow>("t", q2, q3);

    model->execute(0.0, 100.0);

    assert(fabs(round((q1->getValue() - 31.8513)*10000)) < 1);
    assert(fabs(round((q2->getValue() - 18.4003)*10000)) < 1);
    assert(fabs(round((q3->getValue() - 77.1143)*10000)) < 1);
    assert(fabs(round((q4->getValue() - 56.1728)*10000)) < 1);
    assert(fabs(round((q5->getValue() - 16.4612)*10000)) < 1);

    printf("Passou teste Complex function\n");
}