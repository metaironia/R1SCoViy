#ifndef SRC_SIMULATOR_SPU_ISA_RV32I_H
#define SRC_SIMULATOR_SPU_ISA_RV32I_H

#define NEW_ITYPE_INSTRUCTION(InstrName, ...) \
    class InstrName : public ITypeInstruction { \
        void operator() (uint16_t Imm, Register_t &Rs1, Register_t &Rd) override {
            __VA_ARGS__
        }
    };

#define NEW_MEMITYPE_INSTRUCTION(InstrName, ...) \
    class InstrName : public ITypeInstruction { \
        void operator() (uint16_t Imm, Register_t &Rs1, Register_t &Rd,
                         std::shared_ptr<RAMControllerUnit> RAMController) override {
            __VA_ARGS__
        }
    };

NEW_ITYPE_INSTRUCTION(addi, {
    Rd = Rs1 + CraftSignExtImm(getImm(), sizeof(Register_t));
})

#undef NEW_INSTRUCTION

#endif