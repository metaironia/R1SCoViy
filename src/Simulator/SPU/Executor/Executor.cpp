#include "Executor.h"
#include "Simulator/SPU/Executor/InstructionDispatcher.h"
#include "LogHelper/OverwriteMacros.h"

namespace r1scoviy {

ExecutorUnit::ExecutorUnit(ExtensionRegistry &TargetExtensionRegistry, RAMControllerUnit &_RAMController, uint32_t &_PC)
    : Instructions(), RAMController(_RAMController),
      Registers(TargetExtensionRegistry), CurrInstructionParams{}, PC(_PC) {
        
    LOG_DEBUG_("ExecutorUnit constructor called");
}

void ExecutorUnit::executeInstr(uint32_t Instr) {

    LOG_TRACE_("Executor: executing instruction 0x{:08X}", Instr);

    const uint32_t Opcode = InstructionDispatcher::getOpcode(Instr);

    LOG_TRACE_("Executor: opcode is 0x{:X}", Opcode);

    const auto &OpcodesDispatchers = Instructions.getOpcodesDispatchers();
    
    auto DispatcherIt = OpcodesDispatchers.find(Opcode);
    if (DispatcherIt == OpcodesDispatchers.end()) {
        LOG_WARNING_("Executor: no dispatcher found for opcode 0x{:X}", Opcode);
        return;
    }
    const auto &Dispatcher = DispatcherIt->second;

    const uint32_t InstructionID = Dispatcher->getInstrID(Instr);

    LOG_TRACE_("Executor: instruction ID is 0x{:X}", InstructionID);

    const auto &AllInstructions = Instructions.getInstructions();
    auto InstructionIt = AllInstructions.find(InstructionID);
    if (InstructionIt == AllInstructions.end()) {
        LOG_WARNING_("Executor: no instruction found for ID 0x{:X}", InstructionID);
        return;
    }

    LOG_DEBUG_("Executor: executing instruction");
    InstructionIt->second->executeInstr(*this);
}

} // namespace r1scoviy
