#ifndef INSTRUCTION_H
#define INSTRUCTION_H

typedef struct {
    int block;
    int word;
} Address;

typedef struct {
    Address add1;
    Address add2;
    Address add3;
    int opcode;
} Instruction;

Address getAdd1(Instruction* instruction);
void setAdd1(Instruction* instruction, Address add);

Address getAdd2(Instruction* instruction);
void setAdd2(Instruction* instruction, Address add);

Address getAdd3(Instruction* instruction);
void setAdd3(Instruction* instruction, Address add);

int getOpcode(Instruction* instruction);
void setOpcode(Instruction* instruction, int opcode);

#endif // !INSTRUCTION_H