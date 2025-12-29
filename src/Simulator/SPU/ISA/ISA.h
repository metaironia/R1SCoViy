#ifndef SRC_SIMULATOR_SPU_ISA_ISA_H
#define SRC_SIMULATOR_SPU_ISA_ISA_H

#include "src/Simulator/SPU/Executor/Executor.h"

#include "InstructionRegistry.h"
#include "ExtensionRegistry.h"
#include "InstructionTypes.h"

class RISCVISA {
private:
    InstructionRegistry RegisteredInstr;

public:
    class InstrTypeVisitor {
    private:
        ExecutorUnit *Executor;

    public:
        InstrTypeVisitor(ExecutorUnit &TargetExecutor);
        
        void setVisitorExecutor(ExecutorUnit &TargetExecutor);

        void operator()(const NotMemoryTypeInstruction &Instr);
        void operator()(const MemoryTypeInstruction &Instr);
    };

    void executeInstr(ExecutorUnit &TargetExecutor);

private:
    InstrTypeVisitor Visitor;

    using InstructionVariant = std::variant<NotMemoryTypeInstruction, MemoryTypeInstruction>;

    InstructionVariant getTypeOfInstr(uint32_t Instr);
};

#endif