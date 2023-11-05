/* Felipe Braz Marques - 22.1.4030*/

#include <cassert>
#include <cmath>
#include <vector>

#include "funcional_test.h"
#include "../../src/Model.h"
#include "../../src/System.h"
#include "../../src/Flow.h"

using namespace std;

double exponencial(System* const origin, System* const destiny) {
    System *pop1 = origin;
    return 0.01 * pop1->getvalue();
}

// Teste 2
double logistica (System* const o, System* const destiny) {
    System *p2 = destiny;
    return 0.01 * p2->getvalue() * (1 - (p2->getvalue() / 70));
}

void exponentialFuncionalTest() {
    System pop1(100.0, "pop1"), pop2(0.0, "pop2");

    Flow fluxoExponencial(&pop1, &pop2, exponencial, "FluxoExponencial");

    Model modelo("Modelo1", 0.0);

    modelo.add(&pop1);
    modelo.add(&pop2);
    modelo.add(&fluxoExponencial);

    modelo.execute(0.0, 100, 1);

    assert(fabs(pop1.getvalue() - 36.6032) < 0.0001);
    assert(fabs(pop2.getvalue() - 63.3968) < 0.0001);
}

void logisticalFuncionalTest() {
    System p1(100.0, "p1"), p2(10.0, "p2");

    Flow fluxoLogistica(&p1, &p2, logistica, "FluxoLogistica");
    Model modelo("Modelo2", 0.0);

    modelo.add(&p1);
    modelo.add(&p2);
    modelo.add(&fluxoLogistica);

    modelo.execute(0.0, 100, 1);

    assert(fabs(p1.getvalue() - 88.2167) < 0.0001);
    assert(fabs(p2.getvalue() - 21.7833) < 0.0001);
}

void complexFuncionalTest() {
    System 
        Q1(100.0, "Q1"), 
        Q2(0.0, "Q2"), 
        Q3(100.0, "Q3"), 
        Q4(0.0, "Q4"), 
        Q5(0.0, "Q5");

    Flow 
        v(&Q4, &Q1, exponencial, "v"), 
        u(&Q3, &Q4, exponencial, "u"), 
        g(&Q1, &Q3, exponencial, "g"),
        f(&Q1, &Q2, exponencial, "f"), 
        r(&Q2, &Q5, exponencial, "r"), 
        t(&Q2, &Q3, exponencial, "t");

    Model modelo("Modelo3", 0.0);

    modelo.add(&Q1);
    modelo.add(&Q2);
    modelo.add(&Q3);
    modelo.add(&Q4);
    modelo.add(&Q5);

    modelo.add(&v);
    modelo.add(&u);
    modelo.add(&g);
    modelo.add(&f);
    modelo.add(&r);
    modelo.add(&t);

    modelo.execute(0.0, 100, 1);

    assert(fabs(Q1.getvalue() - 31.8513) < 0.0001);
    assert(fabs(Q2.getvalue() - 18.4003) < 0.0001);
    assert(fabs(Q3.getvalue() - 77.1143) < 0.0001);
    assert(fabs(Q4.getvalue() - 56.1728) < 0.0001);
    assert(fabs(Q5.getvalue() - 16.4612) < 0.0001);
}
