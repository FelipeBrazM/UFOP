/**
 * @file unit_model.cpp
 *
 * @brief Este arquivo contém os testes unitários para a classe Model.
 */

#include <cassert>
#include <iostream>
#include "../../src/System.h"
#include "../../src/Flow.h"
#include "../../src/Model.h"
#include "unit_model.h"

using namespace std;

/**
 * @brief Função que executa todos os testes unitários para a classe Model.
 */
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

/**
 * @brief Testa a construção de instâncias da classe Model.
 */
void unit_model_constructor(void) {
    // Teste 1: Construção usando o construtor padrão
    AbstractModel *m1 = new Model();
    assert(m1->getName() == "");
    assert(m1->getTime() == 0.0);
    delete m1;

    // Teste 2: Construção usando o construtor com parâmetros
    Model m2("model name", 10.0);
    assert(m2.getName() == "model name");
    assert(m2.getTime() == 10.0);
}

/**
 * @brief Testa a destruição de instâncias da classe Model.
 */
void unit_model_destructor(void) {
    // A função não tem implementação pois não há necessidade de testar a destruição.
}

/**
 * @brief Testa o método getName da classe Model.
 */
void unit_model_getName() {
    Model m("model name");
    assert(m.getName() == "model name");
}

/**
 * @brief Testa o método setName da classe Model.
 */
void unit_model_setName() {
    Model m;
    m.setName("new model name");
    assert(m.getName() == "new model name");
}

/**
 * @brief Testa o método getTime da classe Model.
 */
void unit_model_getTime() {
    Model m("model name", 0.0);
    assert(m.getTime() == 0.0);
}

/**
 * @brief Testa o método setTime da classe Model.
 */
void unit_model_setTime() {
    Model m;
    m.setTime(87.0);
    assert(m.getTime() == 87.0);
}

/**
 * @brief Testa o método add da classe Model.
 */
void unit_model_add() {
    Model m;
    AbstractSystem *s1 = new System();
    AbstractFlow *f1 = new Flow();

    m.add(s1);
    m.add(f1);

    assert(m.getSystensSize() == 1);
    assert(m.getFlowsSize() == 1);

    delete s1;
    delete f1;
}

/**
 * @brief Testa o método execute da classe Model.
 */
void unit_model_execute() {
    Model m;
    m.execute(0, 10, 1);
    assert(m.getTime() == 10);
}
