#ifndef SRC_SIMULATOR_SPU_ISA_INSTRUCTIONTYPES_H
#define SRC_SIMULATOR_SPU_ISA_INSTRUCTIONTYPES_H

#include "src/Simulator/SPU/Executor/Executor.h"

namespace r1scoviy {

class Instruction {
private:
    uint32_t Opcode;

public:
    virtual void executeInstr(ExecutorUnit &TargetExecutor) const = 0;

    uint32_t getOpcode() { return Opcode; }

    virtual ~Instruction() = default;
};

} // namespace r1scoviy

#endif