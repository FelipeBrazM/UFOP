#include <cassert>
#include <cmath>
#include <vector>

#include "funcional_test.h"
#include "../../src/AbstractSystem.h"
#include "../../src/AbstractModel.h"
#include "../../src/AbstractFlow.h"

using namespace std;

double exponencial(AbstractSystem* const origin, AbstractSystem* const destiny) {
    AbstractSystem *pop1 = origin;
    return 0.01 * pop1->getValue();
}

double logistica (AbstractSystem* const o, AbstractSystem* const destiny) {
    AbstractSystem *p2 = destiny;
    return 0.01 * p2->getValue() * (1 - (p2->getValue() / 70));
}

void exponentialFuncionalTest() {

    AbstractModel *modelo = AbstractModel::createModel("Modelo1", 0.0);

    AbstractSystem *pop1 = modelo->createSystem(100.0, "pop1");
    AbstractSystem *pop2 = modelo->createSystem(0.0, "pop2");

    modelo->createFlow(pop1, pop2, exponencial, "FluxoExponencial");

    modelo->execute(0.0, 100, 1);

    assert(fabs(pop1->getValue() - 36.6032) < 0.0001);
    assert(fabs(pop2->getValue() - 63.3968) < 0.0001);
    printf("Exponential test OK\n\n");

    delete modelo;
}

void logisticalFuncionalTest() {

    AbstractModel *modelo = AbstractModel::createModel("Modelo2", 0.0);

    AbstractSystem *p1 = modelo->createSystem(100.0, "p1");
    AbstractSystem *p2 = modelo->createSystem(10.0, "p2");

    modelo->createFlow(p1, p2, logistica, "FluxoLogistica");

    modelo->execute(0.0, 100, 1);

    assert(fabs(p1->getValue() - 88.2167) < 0.0001);
    assert(fabs(p2->getValue() - 21.7833) < 0.0001);
    printf("Logistical teste OK\n\n");

    delete modelo;
}

void complexFuncionalTest() {

    AbstractModel *modelo = AbstractModel::createModel("Modelo3", 0.0);

    AbstractSystem *Q1 = modelo->createSystem(100.0, "Q1"); 
    AbstractSystem *Q2 = modelo->createSystem(0.0, "Q2");
    AbstractSystem *Q3 = modelo->createSystem(100.0, "Q3"); 
    AbstractSystem *Q4 = modelo->createSystem(0.0, "Q4");
    AbstractSystem *Q5 = modelo->createSystem(0.0, "Q5");

    modelo->createFlow(Q4, Q1, exponencial, "v"); 
    modelo->createFlow(Q3, Q4, exponencial, "u"); 
    modelo->createFlow(Q1, Q3, exponencial, "g");
    modelo->createFlow(Q1, Q2, exponencial, "f"); 
    modelo->createFlow(Q2, Q5, exponencial, "r"); 
    modelo->createFlow(Q2, Q3, exponencial, "t");

    modelo->execute(0.0, 100, 1);

    assert(fabs(Q1->getValue() - 31.8513) < 0.0001);
    assert(fabs(Q2->getValue() - 18.4003) < 0.0001);
    assert(fabs(Q3->getValue() - 77.1143) < 0.0001);
    assert(fabs(Q4->getValue() - 56.1728) < 0.0001);
    assert(fabs(Q5->getValue() - 16.4612) < 0.0001);
    printf("Complex test OK\n");

    delete modelo;
}