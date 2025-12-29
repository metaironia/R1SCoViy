#ifndef SRC_SIMULATOR_SPU_ISA_INSTRUCTIONTYPES_H
#define SRC_SIMULATOR_SPU_ISA_INSTRUCTIONTYPES_H

#include "src/Simulator/Memory/Memory.h"

using Instruction_t = uint32_t;
using InstructionID_t = int;

class InstructionImpl {
public:
    virtual void executeInstr(ExecutorUnit &Executor) const = 0;   
};

class NotMemoryTypeInstruction: public Instruction {
public:
    NotMemoryTypeInstruction(Instruction_t TargetInstr) : Instruction(TargetInstr) {}

    virtual void operator()(RegisterFileUnit &RegisterFile) const = 0;
};


#endif