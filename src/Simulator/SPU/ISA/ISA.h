#ifndef SRC_SIMULATOR_SPU_ISA_ISA_H
#define SRC_SIMULATOR_SPU_ISA_ISA_H

class RISCVISA {
private:
    std::unordered_map<InstrID, ITypeInstruction *> ITypeInstrs;
    std::unordered_map<InstrID, MemITypeInstruction *> MemITypeInstrs;
    std::unordered_map<InstrID, RTypeInstruction *> RTypeInstrs;
    std::unordered_map<InstrID, STypeInstruction *> STypeInstrs;
    std::unordered_map<InstrID, BTypeInstruction *> BTypeInstrs;
    std::unordered_map<InstrID, UTypeInstruction *> UTypeInstrs;
    std::unordered_map<InstrID, JTypeInstruction *> JTypeInstrs;
    std::unordered_map<InstrID, R4TypeInstruction *> R4TypeInstrs;

    class InstrTypeVisitor;

    InstrTypeVisitor Visitor;

public:
    registerExtension();

    executeInstr(ExecutorUnit &TargetExecutor);

private:
    std::variant<IType, MemIType, Rtype, SType,
                 BType, UType, JType, R4Type> getTypeOfInstr(uint32_t Instr);
}

class RISCVISA::InstrTypeVisitor {
private:
    std::unique_ptr<ExecutorUnit> Executor;

    friend ExecutorUnit;

public:
    InstrTypeVisitor(const InstrTypeVisitor &Other);
    InstrTypeVisitor &operator=(const InstrTypeVisitor &Other) = delete;

    ~InstrTypeVisitor();
    
    SetVisitorExecutor(ExecutorUnit &TargetExecutor);

    void operator()(IType &Instr);
    void operator()(MemIType &Instr);
    void operator()(RType &Instr);
    void operator()(SType &Instr);
    void operator()(BType &Instr);
    void operator()(UType &Instr);
    void operator()(JType &Instr);
}

#endif