#include "Executor.h"

namespace r1scoviy {

ExecutorUnit::ExecutorUnit(RAMUnit &RAM, ExtensionRegistry &TargetExtensionRegistry)
    : RAMController(RAM), Registers(), CurrInstructionParams{}, PC(0) {

    
}

void ExecutorUnit::executeInstr(uint32_t Instr) {

    ISA.executeInstr(*this);
}

uint32_t ExecutorUnit::getCurrentInstr() {

    return CurrentInstr;
}

} // namespace r1scoviy
