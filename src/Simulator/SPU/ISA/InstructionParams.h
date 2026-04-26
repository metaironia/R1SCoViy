#ifndef SRC_SIMULATOR_SPU_ISA_INSTRUCTIONPARAMS_H
#define SRC_SIMULATOR_SPU_ISA_INSTRUCTIONPARAMS_H

#include <cstdint>

const int FUNCT3_STARTBIT = 12;
const int FUNCT7_STARTBIT = 25;
const int FUNCT5_STARTBIT = 27;
const int BITWISE_FIXED_IMM_STARTBIT = 25;
const int ULTRA_BITWISE_IMM_STARTBIT = 20;

enum class Opcodes {
    OP_FP = 0x53,
    OP_IMM = 0x13
};

struct InstrParams {
    uint32_t Imm;
    int Rs1;
    int Rs2;
    int Rs3;
    int Rd;
    uint32_t Rm;
};

#endif // SRC_SIMULATOR_SPU_ISA_INSTRUCTIONPARAMS_H