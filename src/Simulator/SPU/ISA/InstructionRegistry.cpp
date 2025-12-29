#include <variant>
#include <string_view>
#include <cassert>
#include <unordered_map>
#include <memory>

#include "InstructionRegistry.h"
#include "InstructionTypes.h"

InstructionRegistry::InstructionRegistry()
    : Visitor(this) {}

void InstructionRegistry::registerInstrs(ExtensionRegistry &CurrentExtensionRegistry,
                                         std::initializer_list<std::string_view> ExtensionsNames) {

    for (const auto &CurrentExtensionName: ExtensionsNames) {

        const Extension *CurrentExtension = CurrentExtensionRegistry.getExtensionByName(CurrentExtensionName);
        if (!CurrentExtension) {
            continue; // TODO: log this
        }

        for (const auto &CurrInstr: CurrentExtension->getExtensionRelatedInstrs()) {

            std::visit(Visitor, CurrInstr);
        }
    }
}

InstructionRegistry::InstrTypeVisitor::InstrTypeVisitor(InstructionRegistry *TargetInstrRegistry)
    : RelatedInstrRegistry(TargetInstrRegistry) {}

void InstructionRegistry::InstrTypeVisitor::operator()(const std::shared_ptr<MemoryTypeInstruction> &Instr) {

    assert(RelatedInstrRegistry);

    RelatedInstrRegistry->MemoryInstrs.getInstrs()[Instr->getID()] = Instr;
}

void InstructionRegistry::InstrTypeVisitor::operator()(const std::shared_ptr<NotMemoryTypeInstruction> &Instr) {

    assert(RelatedInstrRegistry);

    RelatedInstrRegistry->NotMemoryInstrs.getInstrs()[Instr->getID()] = Instr;
}