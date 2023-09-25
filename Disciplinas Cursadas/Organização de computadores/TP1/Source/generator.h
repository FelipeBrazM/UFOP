#ifndef GENERATOR_H
#define GENERATOR_H

#include "cpu.h"

Instruction* generateRandomInstructions(int);

Instruction* generateMultiplicationInstructions(int, int, int, int);

Instruction* generateDivisionInstructions(int, int);

Instruction* generateExponentiationInstructions(int, int);

Instruction* generateFactorialInstructions(int);

Instruction* generateAritmeticProgressionInstructions(int, int, int);

Instruction* readInstructions(char*, int*);

#endif // !GENERATOR_H