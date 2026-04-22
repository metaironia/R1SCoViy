#include <cstdio>

#include "Simulator/SPU/RegisterFile/RegisterFile.h"
#include "Extension.h"

namespace r1scoviy {

void Extension::addNewInstr(std::shared_ptr<Instruction> NewInstruction) {

    Instructions[NewInstruction->getInstrID()] = std::move(NewInstruction);
}

const std::unordered_map<uint32_t, std::shared_ptr<Instruction>> &Extension::getInstructions() const {

    return Instructions;
}

const RegistersType &Extension::getExtensionRegistersType() const {

    return ExtensionRegistersType;
}

void Extension::dump() const {

    for (const auto &Instr: Instructions) {

        fprintf(stderr, "Instruction id: %d\n", Instr.first);
    }
}

} // namespace r1scoviy