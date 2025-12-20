#ifndef SRC_SIMULATOR_SPU_ISA_INSTRUCTIONREGISTRY_H
#define SRC_SIMULATOR_SPU_ISA_INSTRUCTIONREGISTRY_H

class InstructionRegistry {
private:
    std::unordered_map<InstrID, std::shared_ptr<ITypeInstruction>> ITypeInstrs;
    std::unordered_map<InstrID, std::shared_ptr<MemITypeInstruction>> MemITypeInstrs;
    std::unordered_map<InstrID, std::shared_ptr<RTypeInstruction>> RTypeInstrs;
    std::unordered_map<InstrID, std::shared_ptr<STypeInstruction>> STypeInstrs;
    std::unordered_map<InstrID, std::shared_ptr<BTypeInstruction>> BTypeInstrs;
    std::unordered_map<InstrID, std::shared_ptr<UTypeInstruction>> UTypeInstrs;
    std::unordered_map<InstrID, std::shared_ptr<JTypeInstruction>> JTypeInstrs;
    std::unordered_map<InstrID, std::shared_ptr<R4TypeInstruction>> R4TypeInstrs;

    class InstrTypeVisitor;
    InstrTypeVisitor Visitor;

public:
    InstructionRegistry();

    void registerInstrs(ExtensionRegistry &CurrentExtensionRegistry);
};

class InstructionRegistry::InstrTypeVisitor {
private:
    InstructionRegistry *RelatedInstrRegistry;

public:
    InstrTypeVisitor(InstructionRegistry &TargetInstrRegistry);

private:
    void operator()(std::shared_ptr<ITypeInstruction> &Instr);
    void operator()(std::shared_ptr<MemITypeInstruction> &Instr);
    void operator()(std::shared_ptr<RTypeInstruction> &Instr);
    void operator()(std::shared_ptr<STypeInstruction> &Instr);
    void operator()(std::shared_ptr<BTypeInstruction> &Instr);
    void operator()(std::shared_ptr<UTypeInstruction> &Instr);
    void operator()(std::shared_ptr<JTypeInstruction> &Instr);
    void operator()(std::shared_ptr<R4TypeInstruction> &Instr);
    
};

#endif