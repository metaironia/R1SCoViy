#include <vector>
#include <string_view>
#include <cassert>
#include <array>

#include "RegisterFile.h"

RegisterFileUnit::RegisterFileUnit(ExtensionRegistry &TargetExtesionRegistry) {

    const std::vector<std::string_view> &ExtensionNames = TargetExtesionRegistry.getRegisteredExtensionsNames();

    for (const auto &CurrentExtensionName: ExtensionNames) {

        const Extension *CurrentExtension = TargetExtesionRegistry.getExtensionByName(CurrentExtensionName);
        assert(CurrentExtension);
        
        RegistersType CurrentExtensionRegisterTypes = CurrentExtension->getExtensionRegistersType();

        if (RegistersGroups.find(CurrentExtensionRegisterTypes) == RegistersGroups.end())
            RegistersGroups[CurrentExtension->getExtensionRegistersType()].fill(0);
    }
}

Register_t &RegisterFileUnit::getReg(RegistersType CurrentRegistersType, RegisterID_t RegisterID) {

    assert(RegisterID < REGISTERS_NUMBER);

    return RegistersGroups[CurrentRegistersType][RegisterID];
}
