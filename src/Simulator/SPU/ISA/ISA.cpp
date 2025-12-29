#include <cassert>

#include "ISA.h"

void RISCVISA::executeInstr(ExecutorUnit &TargetExecutor) {

    Instruction_t CurrentInstr = TargetExecutor.getCurrentInstr();
    Visitor.setVisitorExecutor(TargetExecutor);

    std::visit(Visitor, getTypeOfInstr(CurrentInstr));
}

RISCVISA::InstructionVariant RISCVISA::getTypeOfInstr(uint32_t Instr) {

// TODO: todo...    
}

RISCVISA::InstrTypeVisitor::InstrTypeVisitor(ExecutorUnit &TargetExecutor)
    : Executor(&TargetExecutor) {}


void RISCVISA::InstrTypeVisitor::setVisitorExecutor(ExecutorUnit &TargetExecutor) {

    if (!Executor && Executor != &TargetExecutor) {

        Executor = &TargetExecutor;
    }
}

void RISCVISA::InstrTypeVisitor::operator()(const NotMemoryTypeInstruction &Instr) {

    assert(Executor);

    (*(Executor->ISA.RegisteredInstr.NotMemoryInstrs.getInstrs()[Instr.getID()]))(Executor->Registers);
}

void RISCVISA::InstrTypeVisitor::operator()(const MemoryTypeInstruction &Instr) {

    assert(Executor);

    (*(Executor->ISA.RegisteredInstr.MemoryInstrs.getInstrs()[Instr.getID()]))(Executor->Registers,
                                                                               Executor->RAMController);
}