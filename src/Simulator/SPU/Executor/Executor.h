#ifndef SRC_SIMULATOR_SPU_EXECUTOR_EXECUTOR_H
#define SRC_SIMULATOR_SPU_EXECUTOR_EXECUTOR_H

#include <memory>

#include "Simulator/Memory/Memory.h"
#include "Simulator/SPU/ISA/InstructionRegistry.h"
#include "Simulator/SPU/RegisterFile/RegisterFile.h"
#include "Simulator/SPU/ISA/InstructionTypes.h"

namespace r1scoviy {

class ExecutorUnit {
private:
    InstructionRegistry Instructions;

    RAMControllerUnit &RAMController;
    RegisterFileUnit Registers;

    InstrParams CurrInstructionParams;

    uint32_t &PC;

public:
    ExecutorUnit(ExtensionRegistry &TargetExtensionRegistry, RAMControllerUnit &_RAMController, uint32_t &_PC);

    RegisterFileUnit &getRegisterFile() { return Registers; }

    RAMControllerUnit &getRAMController() { return RAMController; }

    const InstrParams &getInstructionParams() { return CurrInstructionParams; }

    uint32_t &getPC() { return PC; }

    void executeInstr(uint32_t Instr);
};

} // namespace r1scoviy

#endif