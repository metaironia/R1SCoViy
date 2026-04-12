#include <vector>
#include <string_view>
#include <cassert>
#include <array>

#include "RegisterFile.h"
#include "src/Simulator/SPU/ISA/ExtensionRegistry.h"

namespace r1scoviy {

RegisterFileUnit::RegisterFileUnit(r1scoviy::ExtensionRegistry &TargetExtesionRegistry) {

    const std::vector<std::string_view> &ExtensionNames = TargetExtesionRegistry.getRegisteredExtensionsNames();

    for (const auto &CurrentExtensionName: ExtensionNames) {

        const r1scoviy::Extension *CurrentExtension = TargetExtesionRegistry.getExtensionByName(CurrentExtensionName);
        assert(CurrentExtension);
        
        RegistersType CurrentExtensionRegisterTypes = CurrentExtension->getExtensionRegistersType();

        if (RegistersGroups.find(CurrentExtensionRegisterTypes) == RegistersGroups.end())
            RegistersGroups[CurrentExtension->getExtensionRegistersType()].fill(0);
    }
}

void RegisterFileUnit::writeRegister(RegistersType CurrentRegistersType, uint32_t RegisterID, uint32_t Value) {

    assert(RegisterID < REGISTERS_NUMBER);

    if (RegisterID == 0)
        return;

    RegistersGroups[CurrentRegistersType][RegisterID] = Value;
}

uint32_t RegisterFileUnit::readRegister(RegistersType CurrentRegistersType, uint32_t RegisterID) {

    return RegistersGroups[CurrentRegistersType][RegisterID];
}


} // namespace r1scoviy