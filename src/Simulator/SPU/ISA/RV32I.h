#ifndef SRC_SIMULATOR_SPU_ISA_RV32I_H
#define SRC_SIMULATOR_SPU_ISA_RV32I_H

DEFINE_EXTENSION_(RV32I, 
    DEFINE_ITYPE_INSTRUCTION(addi, {
        Rd = Rs1 + CraftSignExtImm(getImm(), sizeof(Register_t));
    }))


#endif