/* Felipe Braz Marques - 22.1.4030 */

#include <cassert>
#include <cmath>
#include <vector>

#include "funcional_test.h"
#include "../../src/Model.h"
#include "../../src/System.h"
#include "../../src/Flow.h"
 
using namespace std;

double exponencial(AbstractSystem* const origin, AbstractSystem* const destiny) {
    AbstractSystem *pop1 = origin;
    return 0.01 * pop1->getValue();
}

// Teste 2
double logistica (AbstractSystem* const o, AbstractSystem* const destiny) {
    AbstractSystem *p2 = destiny;
    return 0.01 * p2->getValue() * (1 - (p2->getValue() / 70));
}

void exponentialFuncionalTest() {
    AbstractSystem *pop1 = new System(100.0, "pop1");
    AbstractSystem *pop2 = new System(0.0, "pop2");

    AbstractFlow* fluxoExponencial = new Flow(pop1, pop2, exponencial, "FluxoExponencial");

    AbstractModel *modelo = new Model("Modelo1", 0.0);

    modelo->add(pop1);
    modelo->add(pop2);
    modelo->add(fluxoExponencial);

    modelo->execute(0.0, 100, 1);

    assert(fabs(pop1->getValue() - 36.6032) < 0.0001);
    assert(fabs(pop2->getValue() - 63.3968) < 0.0001);
    printf("Exponential test OK\n\n");
}

void logisticalFuncionalTest() {
    AbstractSystem *p1 = new System(100.0, "p1");
    AbstractSystem *p2 = new System(10.0, "p2");

    AbstractFlow *fluxoLogistica = new Flow(p1, p2, logistica, "FluxoLogistica");
    AbstractModel *modelo = new Model("Modelo2", 0.0);

    modelo->add(p1);
    modelo->add(p2);
    modelo->add(fluxoLogistica);

    modelo->execute(0.0, 100, 1);

    assert(fabs(p1->getValue() - 88.2167) < 0.0001);
    assert(fabs(p2->getValue() - 21.7833) < 0.0001);
    printf("Logistical teste OK\n\n");
}

void complexFuncionalTest() {

    AbstractSystem *Q1 = new System(100.0, "Q1"); 
    AbstractSystem *Q2 = new System(0.0, "Q2");
    AbstractSystem *Q3 = new System(100.0, "Q3"); 
    AbstractSystem *Q4 = new System(0.0, "Q4");
    AbstractSystem *Q5 = new System(0.0, "Q5");

    AbstractFlow *v = new Flow(Q4, Q1, exponencial, "v"); 
    AbstractFlow *u = new Flow(Q3, Q4, exponencial, "u"); 
    AbstractFlow *g = new Flow(Q1, Q3, exponencial, "g");
    AbstractFlow *f = new Flow(Q1, Q2, exponencial, "f"); 
    AbstractFlow *r = new Flow(Q2, Q5, exponencial, "r"); 
    AbstractFlow *t = new Flow(Q2, Q3, exponencial, "t");

    AbstractModel *modelo = new Model("Modelo3", 0.0);

    modelo->add(Q1);
    modelo->add(Q2);
    modelo->add(Q3);
    modelo->add(Q4);
    modelo->add(Q5);

    modelo->add(v);
    modelo->add(u);
    modelo->add(g);
    modelo->add(f);
    modelo->add(r);
    modelo->add(t);

    modelo->execute(0.0, 100, 1);

    assert(fabs(Q1->getValue() - 31.8513) < 0.0001);
    assert(fabs(Q2->getValue() - 18.4003) < 0.0001);
    assert(fabs(Q3->getValue() - 77.1143) < 0.0001);
    assert(fabs(Q4->getValue() - 56.1728) < 0.0001);
    assert(fabs(Q5->getValue() - 16.4612) < 0.0001);
    printf("Complex test OK\n");
}