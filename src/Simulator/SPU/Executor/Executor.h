#ifndef SRC_SIMULATOR_SPU_EXECUTOR_EXECUTOR_H
#define SRC_SIMULATOR_SPU_EXECUTOR_EXECUTOR_H

#include <memory>

#include "src/Simulator/Memory/Memory.h"
#include "src/Simulator/SPU/ISA/ISA.h"
#include "src/Simulator/SPU/RegisterFile/RegisterFile.h"
#include "src/Simulator/SPU/ISA/InstructionTypes.h"

class ExecutorUnit {
private:
    RISCVISA ISA;

    RAMControllerUnit RAMController;
    RegisterFileUnit Registers;

    Instruction_t CurrentInstr;
    
    friend RISCVISA::InstrTypeVisitor;

public:
    ExecutorUnit(RAMUnit &RAM, ExtensionRegistry &TargetExtensionRegistry);

    void executeInstr(Instruction_t Instr);

    Instruction_t getCurrentInstr();
};

#endif