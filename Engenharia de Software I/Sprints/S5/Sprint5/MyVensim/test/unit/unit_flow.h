#ifndef UNIT_FLOW_H
#define UNIT_FLOW_H

#include "../../src/Flow.h"
#include "../../src/FlowImpl.h"
#include "../../src/System.h"
#include <cassert>
#include <string>
#include <iostream>

void run_unit_tests_Flow(void);

void unit_Flow_constructor(void);
void unit_Flow_destructor(void);

void unit_Flow_getName(void);
void unit_Flow_setName(void);

void unit_Flow_getTax(void);
void unit_Flow_setTax(void);

void unit_Flow_getSystemInput(void);
void unit_Flow_setSystemInput(void);

void unit_Flow_getSystemOutput(void);
void unit_Flow_setSystemOutput(void);

void unit_Flow_execute(void);

#endif