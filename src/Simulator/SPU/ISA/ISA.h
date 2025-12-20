#ifndef SRC_SIMULATOR_SPU_ISA_ISA_H
#define SRC_SIMULATOR_SPU_ISA_ISA_H

class RISCVISA {
private:
    InstructionRegistry RegisteredInstr;

    class InstrTypeVisitor;
    InstrTypeVisitor Visitor;

    std::shared_ptr<ExtensionManager> Extensions;

public:
    template<typename T,
             typename = std::enable_if_t<std::is_constructible_v<std::vector<std::string>, T>>>
    explicit MyClass(T&& arg) 
        : data_(std::forward<T>(arg)) {}

    executeInstr(ExecutorUnit &TargetExecutor);

private:
    using InstructionVariant = std::variant<IType, MemIType, Rtype, SType, BType, UType, JType, R4Type>;

    InstructionVariant getTypeOfInstr(uint32_t Instr);
}

class RISCVISA::InstrTypeVisitor {
private:
    ExecutorUnit *Executor;

    friend ExecutorUnit;

public:
    InstrTypeVisitor(ExecutorUnit &TargetExecutor);
    
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