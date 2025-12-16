#include "Executor.h"

ExecutorUnit::ExecutorUnit(std::unique_ptr<RAMControllerUnit> &&RAMControllerModule)
    : RAMController(std::move(RAMControllerModule)), ISA(TargetISA), Visitor(this),
      CurrentInstr(0) {}

void ExecutorUnit::executeInstr(uint32_t Instr) {

    ISA.executeInstr(*this);
}

uint32_t ExecutorUnit::getCurrentInstr() {

    return CurrentInstr;
}

