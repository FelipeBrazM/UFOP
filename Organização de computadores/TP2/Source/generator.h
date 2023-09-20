#ifndef GENERATOR_H
#define GENERATOR_H

#include "cpu.h"

Instruction* generateRandomInstructions(int);
Instruction* readInstructions(char*, int*);

#endif // !GENERATOR_H