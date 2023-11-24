/**
 * @file unit_system.cpp
 *
 * @brief Este arquivo contém os testes unitários para a classe System.
 */

#include <cassert>
#include "../../src/System.h"
#include "unit_system.h"

/**
 * @brief Função que executa todos os testes unitários para a classe System.
 */
void run_unit_tests_system(void) {
    unit_system_constructor();
    unit_system_destructor();
    unit_system_getName();
    unit_system_setName();
    unit_system_getValue();
    unit_system_setValue();
}

/**
 * @brief Testa a construção de instâncias da classe System.
 */
void unit_system_constructor() {
    // Teste 1: Construção usando o construtor padrão
    AbstractSystem *system1 = new System();
    assert(system1->getName() == "");
    assert(system1->getValue() == 0.0);
    delete system1;

    // Teste 2: Construção usando o construtor com parâmetros
    System system2(10.0, "system name");
    assert(system2.getName() == "system name");
    assert(system2.getValue() == 10.0);
}

/**
 * @brief Testa a destruição de instâncias da classe System.
 */
void unit_system_destructor(void) {
    // A função não tem implementação pois não há necessidade de testar a destruição.
}

/**
 * @brief Testa o método getName da classe System.
 */
void unit_system_getName(void) {
    System system(0, "system name");
    assert(system.getName() == "system name");
}

/**
 * @brief Testa o método setName da classe System.
 */
void unit_system_setName(void) {
    System system(0, "system name");
    system.setName("new system name");
    assert(system.getName() == "new system name");
}

/**
 * @brief Testa o método getValue da classe System.
 */
void unit_system_getValue(void) {
    System system(10.0, "system name");
    assert(system.getValue() == 10.0);
}

/**
 * @brief Testa o método setValue da classe System.
 */
void unit_system_setValue(void) {
    System system(0, "");
    system.setValue(10.0);
    assert(system.getValue() == 10.0);
}
