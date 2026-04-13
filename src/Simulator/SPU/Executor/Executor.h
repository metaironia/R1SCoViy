#ifndef SRC_SIMULATOR_SPU_EXECUTOR_EXECUTOR_H
#define SRC_SIMULATOR_SPU_EXECUTOR_EXECUTOR_H

#include <memory>

#include "src/Simulator/Memory/Memory.h"
#include "src/Simulator/SPU/ISA/InstructionRegistry.h"
#include "src/Simulator/SPU/RegisterFile/RegisterFile.h"
#include "src/Simulator/SPU/ISA/InstructionTypes.h"

namespace r1scoviy {

class ExecutorUnit {
private:
    InstructionRegistry Instructions;

    RAMControllerUnit RAMController;
    RegisterFileUnit Registers;

    InstrParams CurrInstructionParams;

    uint32_t &PC;

public:
    ExecutorUnit(ExtensionRegistry &TargetExtensionRegistry, uint32_t &PC);

    RegisterFileUnit &getRegisterFile() { return Registers; }

    RAMControllerUnit &getRAMController() { return RAMController; }

    const InstrParams &getInstructionParams() { return CurrInstructionParams; }

    uint32_t &getPC() { return PC; }

    void executeInstr(uint32_t Instr);
};

} // namespace r1scoviy

#endif