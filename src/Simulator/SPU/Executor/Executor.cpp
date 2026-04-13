#include "Executor.h"
#include "src/Simulator/SPU/Executor/InstructionDispatcher.h"

namespace r1scoviy {

ExecutorUnit::ExecutorUnit(ExtensionRegistry &TargetExtensionRegistry, uint32_t &_PC)
    : Instructions(), RAMController(), Registers(TargetExtensionRegistry), CurrInstructionParams{}, PC(_PC) {}

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
