#include "Executor.h"
#include "src/Simulator/SPU/Executor/InstructionDispatcher.h"

namespace r1scoviy {

ExecutorUnit::ExecutorUnit(RAMUnit &RAM, ExtensionRegistry &TargetExtensionRegistry)
    : RAMController(RAM), Registers(TargetExtensionRegistry), CurrInstructionParams{}, PC(0) {

    
}

void ExecutorUnit::executeInstr(uint32_t Instr) {

    const uint32_t Opcode = InstructionDispatcher::getOpcode(Instr);

    const auto &OpcodesDispatchers = Instructions.getOpcodesDispatchers();
    
    auto DispatcherIt = OpcodesDispatchers.find(Opcode);
    if (DispatcherIt == OpcodesDispatchers.end()) {
        return;
    }
    const auto &Dispatcher = DispatcherIt->second;

    const uint32_t InstructionID = Dispatcher->getInstrID(Instr);

    const auto &AllInstructions = Instructions.getInstructions();
    auto InstructionIt = AllInstructions.find(InstructionID);
    if (InstructionIt == AllInstructions.end()) {
        return;
    }

    InstructionIt->second->executeInstr(*this);
}

} // namespace r1scoviy
