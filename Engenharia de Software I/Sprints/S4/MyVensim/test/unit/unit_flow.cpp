/**
 * @file unit_flow.cpp
 *
 * @brief Este arquivo contém os testes unitários para a classe Flow.
 */

#include <cassert>
#include "../../src/System.h"
#include "../../src/Flow.h"
#include "unit_flow.h"

/**
 * @brief Função que executa todos os testes unitários para a classe Flow.
 */
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

/**
 * @brief Função de teste usada para o método execute da classe Flow.
 *
 * @param test1 Um ponteiro para um AbstractSystem.
 * @param test2 Um ponteiro para outro AbstractSystem.
 * @return Um valor de teste (1 neste caso).
 */
double test(AbstractSystem* test1, AbstractSystem* test2) {
    return 1;
}

/**
 * @brief Testa a construção de instâncias da classe Flow.
 */
void unit_flow_constructor(void) {
    // Teste 1: Construção usando o construtor padrão
    AbstractFlow* f1 = new Flow();
    assert(f1->getName() == "");
    assert(f1->getOrigin() == nullptr);
    assert(f1->getDestiny() == nullptr);
    delete f1;

    // Teste 2: Construção usando o construtor com parâmetros
    AbstractSystem *s1 = new System();
    AbstractSystem *s2 = new System();
    Flow f2(s1, s2, test, "flow name");
    assert(f2.getName() == "flow name");
    assert(f2.getOrigin() == s1);
    assert(f2.getDestiny() == s2);
    delete s1;
    delete s2;
}

/**
 * @brief Testa a destruição de instâncias da classe Flow.
 */
void unit_flow_destructor(void) {
    // A função não tem implementação pois não há necessidade de testar a destruição.
}

/**
 * @brief Testa o método getName da classe Flow.
 */
void unit_flow_getName() {
    AbstractFlow* f = new Flow(nullptr, nullptr, test, "flow name");
    assert(f->getName() == "flow name");
    delete f;
}

/**
 * @brief Testa o método setName da classe Flow.
 */
void unit_flow_setName() {
    AbstractFlow* f = new Flow(nullptr, nullptr, test, "flow name");
    f->setName("new flow name");
    assert(f->getName() == "new flow name");
    delete f;
}

/**
 * @brief Testa o método getValue da classe Flow.
 */
void unit_flow_getValue() {
    AbstractFlow* f = new Flow();
    assert(f->getValue() == 0.0);
    delete f;
}

/**
 * @brief Testa o método setValue da classe Flow.
 */
void unit_flow_setValue() {
    AbstractFlow* f = new Flow();
    f->setValue(15.6);
    assert(f->getValue() == 15.6);
    delete f;
}

/**
 * @brief Testa o método getOrigin da classe Flow.
 */
void unit_flow_getOrigin() {
    AbstractSystem *s1 = new System();
    AbstractFlow* f = new Flow(s1, nullptr, test, "flow name");
    assert(f->getOrigin() == s1);
    delete s1;
    delete f;
}

/**
 * @brief Testa o método setOrigin da classe Flow.
 */
void unit_flow_setOrigin() {
    System *s1 = new System();
    AbstractFlow* f = new Flow();
    f->setOrigin(s1);
    assert(f->getOrigin() == s1);
    delete s1;
    delete f;
}

/**
 * @brief Testa o método getDestiny da classe Flow.
 */
void unit_flow_getDestiny() {
    System *s1 = new System();
    AbstractFlow *f = new Flow(nullptr, s1, test, "flow name");
    assert(f->getDestiny() == s1);
    delete s1;
    delete f;
}

/**
 * @brief Testa o método setDestiny da classe Flow.
 */
void unit_flow_setDestiny() {
    AbstractSystem *s1 = new System();
    AbstractFlow *f = new Flow();
    f->setDestiny(s1);
    assert(f->getDestiny() == s1);
    delete s1;
    delete f;
}

/**
 * @brief Testa o método execute da classe Flow.
 */
void unit_flow_execute() {
    AbstractFlow *f = new Flow(nullptr, nullptr, test, "flow name");
    f->execute();
    assert(f->getValue() == 1);
    delete f;
}
