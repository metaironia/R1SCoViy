#include "Executor.h"
#include "src/Simulator/SPU/Executor/InstructionDispatcher.h"

namespace r1scoviy {

ExecutorUnit::ExecutorUnit(RAMUnit &RAM, ExtensionRegistry &TargetExtensionRegistry)
    : RAMController(RAM), Registers(), CurrInstructionParams{}, PC(0) {

    
}

void ExecutorUnit::executeInstr(uint32_t Instr) {

    Instructions. InstructionDispatcher::getOpcode(Instr);
}

uint32_t ExecutorUnit::getCurrentInstr() {

    return CurrentInstr;
}

} // namespace r1scoviy
