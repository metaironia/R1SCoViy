#ifndef SRC_SIMULATOR_SPU_ISA_DEFINEINSTRUCTIONSDSL_H
#define SRC_SIMULATOR_SPU_ISA_DEFINEINSTRUCTIONSDSL_H

#include <string_view>

#include "Extension.h"

#define GET_INT_REG_(RegID)  RegisterFile.getReg(RegistersType::INTEGER_REGS, RegID)

#define REG_RD_              GET_INT_REG_(getRdNum())
#define REG_RS1_             GET_INT_REG_(getRs1Num())
#define REG_RS2_             GET_INT_REG_(getRs2Num())

#define DEFINE_EXTENSION_(ExtensionName, ...)                                      \
    class Extension##ExtensionName : public Extension {                            \
    public:                                                                        \
        const std::string_view getName() const override { return #ExtensionName; } \
                                                                                   \
        Extension##ExtensionName() {                                               \
                                                                                   \
            __VA_ARGS__;                                                           \
        }                                                                          \
    };

#define DEFINE_ITYPE_INSTRUCTION_(InstrName, Op, Funct3, ...)  {              \
        class InstrName : public ITypeInstruction {                           \
        public:                                                               \
            void operator()(RegisterFileUnit &RegisterFile) const override {  \
                __VA_ARGS__                                                   \
            }                                                                 \
                                                                              \
            InstructionID_t getID() const override { return 0b##Op##Funct3; } \
                                                                              \
        };                                                                    \
                                                                              \
        addNewInstr(std::make_shared<InstrName>());                           \
    }

#endif