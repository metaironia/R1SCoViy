#include "Executor.h"
#include "Simulator/SPU/Executor/InstructionDispatcher.h"
#include "LogHelper/OverwriteMacros.h"
#include "Simulator/SPU/ISA/InstructionTypes.h"

namespace r1scoviy {

ExecutorUnit::ExecutorUnit(ExtensionRegistry &TargetExtensionRegistry, RAMControllerUnit &_RAMController, uint32_t &_PC)
    : Instructions(TargetExtensionRegistry), RAMController(_RAMController),
      Registers(TargetExtensionRegistry), CurrInstructionParams{}, PC(_PC) {
        
    LOG_DEBUG_("ExecutorUnit constructor called");
}

SpuState ExecutorUnit::executeInstr(uint32_t Instr) {

    LOG_DEBUG_("Executor: executing instruction 0x{:08X}", Instr);

    uint32_t Opcode = InstructionDispatcher::getOpcode(Instr);

    LOG_DEBUG_("Executor: opcode is 0x{:X}", Opcode);
    
    if (Opcode == static_cast<uint32_t>(Opcodes::OP_FP)) {
        
        Opcode = FloatTypeRoundingInstructionDispatcher::getOpcode(Instr);
    }

    std::shared_ptr<InstructionDispatcher> Dispatcher;

    if (Opcode == static_cast<uint32_t>(Opcodes::OP_IMM))
        Dispatcher = ITypeInstructionDispatcher::getProperITypeDispatcher(Instr);
    
    else {

        const auto &OpcodesDispatchers = Instructions.getOpcodesDispatchers();
        
        auto DispatcherIt = OpcodesDispatchers.find(Opcode);
        if (DispatcherIt == OpcodesDispatchers.end()) {

            LOG_WARNING_("Executor: no dispatcher found for opcode 0x{:X}", Opcode);
            
            return SpuState::Stop;
        }
        
        Dispatcher = DispatcherIt->second;
    }

    const uint32_t InstructionID = Dispatcher->getInstrID(Instr);

    LOG_DEBUG_("Executor: instruction ID is 0x{:X}", InstructionID);

    const auto &AllInstructions = Instructions.getInstructions();
    auto InstructionIt = AllInstructions.find(InstructionID);
    if (InstructionIt == AllInstructions.end()) {

        LOG_WARNING_("Executor: no instruction found for ID 0x{:X}", InstructionID);

        return SpuState::Stop;
    }

    Dispatcher->setInstrParams(Instr, CurrInstructionParams);
    LOG_DEBUG_("Executor: Curr instruction params: Imm = {}(hex 0x{:08X}), Rs1 = {}, Rs2 = {}, Rd = {}",
              CurrInstructionParams.Imm, CurrInstructionParams.Imm,
              CurrInstructionParams.Rs1, CurrInstructionParams.Rs2, 
              CurrInstructionParams.Rd);

    LOG_DEBUG_("Executor: executing instruction");
    InstructionIt->second->executeInstr(*this);

    return SpuState::Run;
}

} // namespace r1scoviy
