#include <cstdio>

#include "src/Simulator/SPU/RegisterFile/RegisterFile.h"
#include "Extension.h"

namespace r1scoviy {

void Extension::addNewInstr(std::shared_ptr<Instruction> NewInstruction) {

    Instructions[NewInstruction->getOpcode()] = NewInstruction;
}

RegistersType Extension::getExtensionRegistersType() const {

    return ExtensionRegistersType;
}

void Extension::dump() const {

    for (const auto &Instr: Instructions) {

        fprintf(stderr, "Instruction id: %d\n", Instr.first);
    }
}

} // namespace r1scoviy