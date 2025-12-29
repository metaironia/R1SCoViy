#include <vector>

#include "src/Simulator/SPU/RegisterFile/RegisterFile.h"
#include "Extension.h"

const std::vector<Extension::InstructionPtrVariant> &Extension::getExtensionRelatedInstrs() const {

    return ExtensionRelatedInstrs;
}

RegistersType Extension::getExtensionRegistersType() const {

    return ExtensionRegistersType;
}

