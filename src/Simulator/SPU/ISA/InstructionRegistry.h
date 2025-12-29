#ifndef SRC_SIMULATOR_SPU_ISA_INSTRUCTIONREGISTRY_H
#define SRC_SIMULATOR_SPU_ISA_INSTRUCTIONREGISTRY_H

#include <unordered_map>
#include <memory>
#include <string_view>

#include "InstructionTypes.h"
#include "ExtensionRegistry.h"
#include "ISA.h"

class InstructionRegistry {
private:
    template <typename InstructionType>
    class InstructionTypeHashMap {
    private:
        using InstructionsHashMap = std::unordered_map<InstructionID_t, std::shared_ptr<InstructionType>>;

        InstructionsHashMap Instrs;
    
    public:
        InstructionsHashMap &getInstrs() { return Instrs; }
    };

    InstructionTypeHashMap<MemoryTypeInstruction> MemoryInstrs;
    InstructionTypeHashMap<NotMemoryTypeInstruction> NotMemoryInstrs;

    friend RISCVISA::InstrTypeVisitor;

    class InstrTypeVisitor {
    private:
        InstructionRegistry *RelatedInstrRegistry;

    public:
        InstrTypeVisitor(InstructionRegistry *TargetInstrRegistry);

        void operator()(const std::shared_ptr<MemoryTypeInstruction> &Instr);
        void operator()(const std::shared_ptr<NotMemoryTypeInstruction> &Instr);
    };

    InstrTypeVisitor Visitor;

public:
    InstructionRegistry();

    void registerInstrs(ExtensionRegistry &CurrentExtensionRegistry,
                        std::initializer_list<std::string_view> ExtensionsNames);
};

#endif