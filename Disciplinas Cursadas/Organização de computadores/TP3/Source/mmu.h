#ifndef MMU_H
#define MMU_H

#include "memory.h"
#include "instruction.h"
#include "cpu.h"

Line* MMUSearchOnMemorys(Address, Machine*);
int memoryRAMMApping(int adress, RAM *ram);
int blockFromRAMWillBeRemoved(RAM *ram);

#endif // !MMU_H