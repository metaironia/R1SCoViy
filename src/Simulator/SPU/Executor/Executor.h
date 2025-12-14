#ifndef SRC_SIMULATOR_SPU_EXECUTOR_H
#define SRC_SIMULATOR_SPU_EXECUTOR_H

class ExecutorUnit {
private:
    RISCVISA ISA;

    std::unique_ptr<RAMControllerUnit> RAMController;
    RegisterFileUnit Registers;

public:
    ExecutorUnit(std::unique_ptr<RAMControllerUnit> &&RAMControllerModule);

    ExecutorUnit(const &ExecutorUnit Other);
    ExecutorUnit &operator=(const &ExecutorUnit Other);

    ~ExecutorUnit();

    void executeInstr(uint32_t CurrentInstr);

private:
    struct InstrTypeVisitor;

    std::variant<IType, MemIType, Rtype, SType,
                 BType, UType, JType, R4Type> getTypeOfInstr(uint32_t CurrentInstr);
}

struct ExecutorUnit::InstrTypeVisitor {
    
    void operator()(IType &Instr);
    void operator()(MemIType &Instr);
    void operator()(RType &Instr);
    void operator()(SType &Instr);
    void operator()(BType &Instr);
    void operator()(UType &Instr);
    void operator()(JType &Instr);

    friend ExecutorUnit;
}

#endif