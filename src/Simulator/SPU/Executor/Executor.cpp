#include <memory>

#include "src/Simulator/SPU/ISA/ISA.h"
#include "Executor.h"

ExecutorUnit::ExecutorUnit(RAMUnit &RAM, ExtensionRegistry &TargetExtensionRegistry)
    : RAMController(RAM), ISA(TargetExtensionRegistry), CurrentInstr(0), Registers() {}

void ExecutorUnit::executeInstr(uint32_t Instr) {

    ISA.executeInstr(*this);
}

uint32_t ExecutorUnit::getCurrentInstr() {

    return CurrentInstr;
}

