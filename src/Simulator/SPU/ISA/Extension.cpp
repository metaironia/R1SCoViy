#include "Extension.h"

void Extension::addNewInstr(std::unique_ptr<Instruction> NewInstruction) {

    ExtensionRelatedInstrs.push_back(std::move(NewInstruction));
}
