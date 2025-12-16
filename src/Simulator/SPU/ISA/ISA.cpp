#include "ISA.h"


RISCVISA::registerExtension()

RISCVISA::executeInstr(ExecutorUnit &TargetExecutor) {

    CurrentInstr = TargetExecutor.getCurrentInstruction();
    SetVisitorExecutor(TargetExecutor);

    std::visit(Visitor, getTypeOfInstr(CurrentInstr));
}

std::variant<IType, MemIType, Rtype, SType,
             BType, UType, JType, R4Type> RISCVISA::getTypeOfInstr(uint32_t Instr) {


    
}

RISCVISA::InstrTypeVisitor::InstrTypeVisitor(const InstrTypeVisitor &Other)
    : Executor() {}

RISCVISA::InstrTypeVisitor::~InstrTypeVisitor() {

    Executor.release();
}

RISCVISA::InstrTypeVisitor::SetVisitorExecutor(ExecutorUnit &TargetExecutor) {

    if (!Executor && Executor != &TargetExecutor) {

        Executor.release();
        Executor = std::unique_ptr<ExecutorUnit>(&TargetExecutor);
    }
}

void RISCVISA::InstrTypeVisitor::operator()(IType &Instr) {

    assert(Executor);

    ITypeInstrs[Instr.getId()](Executor->Registers.getReg(Instr.getRs1Num()), 
                               Executor->Registers.getReg(Instr.getRdNum()));
}

void RISCVISA::InstrTypeVisitor::operator()(MemIType &Instr) {

    assert(Executor);

    MemITypeInstrs[Instr.getId()](Executor->Registers.getReg(Instr.getRs1Num()), 
                                  Executor->Registers.getReg(Instr.getRdNum()),
                                  Executor->RAMController);
}

void RISCVISA::InstrTypeVisitor::operator()(RType &Instr) {

    assert(Executor);

    RTypeInstrs[Instr.getId()](Executor->Registers.getReg(Instr.getRs2Num()), 
                               Executor->Registers.getReg(Instr.getRs1Num()),
                               Executor->Registers.getReg(Instr.getRdNum()));
}

void RISCVISA::InstrTypeVisitor::operator()(SType &Instr) {

    assert(Executor);

    STypeInstrs[Instr.getId()](Executor->Registers.getReg(Instr.getRs2Num()),
                               Executor->Registers.getReg(Instr.getRs1Num()),
                               Executor->RAMController);
}

void RISCVISA::InstrTypeVisitor::operator()(BType &Instr) {

    assert(Executor);

    BTypeInstrs[Instr.getId()](Executor->Registers.getReg(Instr.getRs2Num()),
                               Executor->Registers.getReg(Instr.getRs1Num()));
}

void RISCVISA::InstrTypeVisitor::operator()(UType &Instr) {

    assert(Executor);

    BTypeInstrs[Instr.getId()](Executor->Registers.getReg(Instr.getRdNum()));
}

void RISCVISA::InstrTypeVisitor::operator()(JType &Instr) {

    assert(Executor);

    JTypeInstrs[Instr.getId()](Executor->Registers.getReg(Instr.getRdNum())),
}

void RISCVISA::InstrTypeVisitor::operator()(R4Type &Instr) {

    assert(Executor);

    R4TypeInstrs[Instr.getId()](Executor->Registers.getReg(Instr.getFs3Num()),
                                Executor->Registers.getReg(Instr.getFs2Num()),
                                Executor->Registers.getReg(Instr.getFs1Num()),
                                Executor->Registers.getReg(Instr.getFdNum()));
}