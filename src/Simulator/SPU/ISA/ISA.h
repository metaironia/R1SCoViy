#ifndef SRC_SIMULATOR_SPU_ISA_ISA_H
#define SRC_SIMULATOR_SPU_ISA_ISA_H

class RISCVISA {
private:
    InstructionRegistry RegisteredInstr;

    class InstrTypeVisitor;
    InstrTypeVisitor Visitor;

    std::shared_ptr<ExtensionManager> Extensions;

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