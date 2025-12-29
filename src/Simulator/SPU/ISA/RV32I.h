#ifndef SRC_SIMULATOR_SPU_ISA_RV32I_H
#define SRC_SIMULATOR_SPU_ISA_RV32I_H

#include "src/Simulator/SPU/RegisterFile/RegisterFile.h"
#include "DefineInstructionsDSL.h"

DEFINE_EXTENSION_(RV32I, 
    DEFINE_ITYPE_INSTRUCTION_(addi, 0010011, 000, {
        REG_RD_ = REG_RS1_ + CraftSignExtImm(getImm(), sizeof(Register_t));
    }))


#endif