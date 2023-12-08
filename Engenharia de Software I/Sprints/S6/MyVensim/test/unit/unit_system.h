#ifndef UNIT_SYSTEM_H
#define UNIT_SYSTEM_H

#include <cassert>
#include "../../src/System.h"
#include "../../src/SystemImpl.h"


void run_unit_tests_System(void);

void unit_System_constructor(void);
void unit_System_destructor(void);

void unit_System_getName(void);
void unit_System_setName(void);

void unit_System_getValue(void);
void unit_System_setValue(void);

#endif