#ifndef SRC_SIMULATOR_SPU_EXECUTOR_EXECUTOR_H
#define SRC_SIMULATOR_SPU_EXECUTOR_EXECUTOR_H

#include <memory>

#include "src/Simulator/Memory/Memory.h"
#include "src/Simulator/SPU/ISA/InstructionRegistry.h"
#include "src/Simulator/SPU/RegisterFile/RegisterFile.h"

namespace r1scoviy {

class ExecutorUnit {
private:
    InstructionRegistry Instructions;

    RAMControllerUnit RAMController;
    RegisterFileUnit Registers;

    struct InstrParams {
        uint32_t Imm;
        int Rs1;
        int Rs2;
        int Rd;
    } CurrInstructionParams;

    uint32_t PC;

public:
    ExecutorUnit(RAMUnit &RAM, ExtensionRegistry &TargetExtensionRegistry);

    RegisterFileUnit &getRegisterFile() { return Registers; }

    const InstrParams &getInstructionParams() { return CurrInstructionParams; }

    uint32_t &getPC() { return PC; }

    void executeInstr(uint32_t Instr);
};

} // namespace r1scoviy

#endif