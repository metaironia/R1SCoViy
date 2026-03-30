#ifndef SRC_SIMULATOR_SPU_ISA_DEFINEINSTRUCTIONSDSL_H
#define SRC_SIMULATOR_SPU_ISA_DEFINEINSTRUCTIONSDSL_H

#include <string_view>

#include "Extension.h"

#define GET_INT_REG_(RegID)  RegisterFile.getReg(RegistersType::INTEGER_REGS, RegID)

#define REG_RD_              GET_INT_REG_(getRdNum())
#define REG_RS1_             GET_INT_REG_(getRs1Num())
#define REG_RS2_             GET_INT_REG_(getRs2Num())

#endif