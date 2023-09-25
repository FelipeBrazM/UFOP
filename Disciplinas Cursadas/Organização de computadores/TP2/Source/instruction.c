#include "instruction.h"

Address getAdd1(Instruction* instruction) { return instruction->add1; }
void setAdd1(Instruction* instruction, Address add) { instruction->add1 = add; }

Address getAdd2(Instruction* instruction) { return instruction->add2; }
void setAdd2(Instruction* instruction, Address add) { instruction->add2 = add; }

Address getAdd3(Instruction* instruction) { return instruction->add3; }
void setAdd3(Instruction* instruction, Address add) { instruction->add3 = add; }

int getOpcode(Instruction* instruction) { return instruction->opcode; }
void setOpcode(Instruction* instruction, int opcode) { instruction->opcode = opcode; }
