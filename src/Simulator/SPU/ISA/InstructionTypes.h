#ifndef SRC_SIMULATOR_SPU_ISA_INSTRUCTIONTYPES_H
#define SRC_SIMULATOR_SPU_ISA_INSTRUCTIONTYPES_H

#include <cstdint>

namespace r1scoviy {

class ExecutorUnit;

class Instruction {
public:
    virtual void executeInstr(ExecutorUnit &TargetExecutor) const = 0;

    virtual ~Instruction() = default;
};

} // namespace r1scoviy

#endif