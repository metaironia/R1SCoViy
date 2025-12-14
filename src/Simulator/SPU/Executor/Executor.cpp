#include "Executor.h"

ExecutorUnit::ExecutorUnit(std::unique_ptr<RAMControllerUnit> &&RAMControllerModule)
    : RAMController(std::move(RAMControllerModule)) {}

ExecutorUnit::ExecutorUnit(const &ExecutorUnit Other)
    : RAMController(Other.get()) {}

ExecutorUnit::ExecutorUnit &operator=(const &ExecutorUnit Other) {
    
    RAMController.release();
    RAMController.reset(Other.get());

    return *this;
}

ExecutorUnit::~ExecutorUnit() {

    RAMController.release();
}

void ExecutorUnit::executeInstr(uint32_t CurrentInstr) {

    std::visit(InstrTypeVisitor(), getTypeOfInstr(CurrentInstr));
}

void ExecutorUnit::InstrTypeVisitor::operator()(IType &Instr) {

    ITypeInstrs[Instr.getId()](Instr.getImm(), 
                               Registers.getReg(Instr.getRdNum()), 
                               Registers.getReg(Instr.getRs1Num()));
}

void ExecutorUnit::InstrTypeVisitor::operator()(MemIType &Instr) {

    MemITypeInstrs[Instr.getId()](Instr.getImm(), 
                                  Registers.getReg(Instr.getRdNum()), 
                                  Registers.getReg(Instr.getRs1Num()),
                                  RAMController.get);
}

void ExecutorUnit::InstrTypeVisitor::operator()(RType &Instr) {


}

void ExecutorUnit::InstrTypeVisitor::operator()(SType &Instr) {


}

void ExecutorUnit::InstrTypeVisitor::operator()(BType &Instr) {


}

void ExecutorUnit::InstrTypeVisitor::operator()(UType &Instr) {


}

void ExecutorUnit::InstrTypeVisitor::operator()(JType &Instr) {


}
