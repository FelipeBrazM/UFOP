#ifndef UNIT_MODEL_H
#define UNIT_MODEL_H

#include "../../src/Flow.h"
#include "../../src/FlowImpl.h"
#include "../../src/System.h"
#include "../../src/Model.h"
#include <cassert>
#include <iostream>
#include <cmath>

void run_unit_tests_Model(void);

void unit_Model_constructor(void);
void unit_Model_destructor(void);

void unit_Model_getName(void);
void unit_Model_setName(void);

void unit_Model_getTimeInitial(void);
void unit_Model_setTimeInitial(void);

void unit_Model_getTimeFinal(void);
void unit_Model_setTimeFinal(void);

void unit_Model_setTime(void);

void unit_Model_add(void);
void unit_Model_removal(void);

// void unit_Model_systemBegin(void);

void unit_Model_execute(void);



#endif