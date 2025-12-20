#include "InstructionRegistry.h"

InstructionRegistry::InstructionRegistry()
    : InstrTypeVisitor(this) {}


void InstructionRegistry::registerInstrs(ExtensionRegistry &CurrentExtensionRegistry) {

    for (const auto &CurrExtension: CurrentExtensionRegistry)
        for (const auto &CurrInstr: CurrExtension) {

            std::visit(Visitor(), CurrInstr);
        }
}

InstructionRegistry::InstrTypeVisitor::InstrTypeVisitor(InstructionRegistry &TargetInstrRegistry)
    : RelatedInstrRegistry(&TargetInstrRegistry) {}

void operator()(std::shared_ptr<ITypeInstruction> &Instr) {

    ITypeInstrs[Instr->getInstrID()] = Instr;
}

void operator()(std::shared_ptr<MemITypeInstruction> &Instr) {

    MemITypeInstrs[Instr->getInstrID()] = Instr;
}

void operator()(std::shared_ptr<RTypeInstruction> &Instr) {

    RTypeInstrs[Instr->getInstrID()] = Instr;
}

void operator()(std::shared_ptr<STypeInstruction> &Instr) {

    STypeInstrs[Instr->getInstrID()] = Instr;
}

void operator()(std::shared_ptr<BTypeInstruction> &Instr) {

    BTypeInstrs[Instr->getInstrID()] = Instr;
}

void operator()(std::shared_ptr<UTypeInstruction> &Instr) {

    UTypeInstrs[Instr->getInstrID()] = Instr;
}

void operator()(std::shared_ptr<JTypeInstruction> &Instr) {

    JTypeInstrs[Instr->getInstrID()] = Instr;
}

void operator()(std::shared_ptr<R4TypeInstruction> &Instr) {

    R4TypeInstrs[Instr->getInstrID()] = Instr;
}
