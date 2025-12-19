#ifndef SRC_SIMULATOR_SPU_ISA_DEFINEINSTRUCTIONSDSL_H
#define SRC_SIMULATOR_SPU_ISA_DEFINEINSTRUCTIONSDSL_H

#define DEFINE_EXTENSION_(ExtensionName, ...)                                \
    class Extension##ExtensionName : public Extension {                      \
    public:                                                                  \
        const std::string_view getName() override { return #ExtensionName; } \
                                                                             \
        Extension##ExtensionName() : {                                       \
                                                                             \
            __VA_ARGS__;                                                     \
        }                                                                    \
    };

#define DEFINE_ITYPE_INSTRUCTION_(InstrName, ...)  {                                   \
        class InstrName : public ITypeInstruction {                                    \
            void operator() (uint16_t Imm, Register_t &Rs1, Register_t &Rd) override { \
                __VA_ARGS__                                                            \
            }                                                                          \
        };                                                                             \
                                                                                       \
        addNewInstr(std::make_unique<InstrName>());                                    \
    }

#define DEFINE_MEMITYPE_INSTRUCTION_(InstrName, ...)  {                                  \
        class InstrName : public ITypeInstruction {                                      \
            void operator() (uint16_t Imm, Register_t &Rs1, Register_t &Rd,              \
                            std::shared_ptr<RAMControllerUnit> RAMController) override { \
                __VA_ARGS__                                                              \
            }                                                                            \
        };                                                                               \
                                                                                         \
        addNewInstr(std::make_unique<InstrName>());                                      \
    }

#endif