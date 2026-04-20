#include <vector>
#include <string_view>
#include <cassert>
#include <array>

#include "RegisterFile.h"
#include "Simulator/SPU/ISA/ExtensionRegistry.h"
#include "LogHelper/OverwriteMacros.h"

namespace r1scoviy {

RegisterFileUnit::RegisterFileUnit(r1scoviy::ExtensionRegistry &TargetExtesionRegistry)
    : RegistersGroups() {

    LOG_DEBUG_("RegisterFileUnit constructor called");

    const std::vector<std::string_view> &ExtensionNames = TargetExtesionRegistry.getRegisteredExtensionsNames();

    for (const auto &CurrentExtensionName: ExtensionNames) {

        const r1scoviy::Extension *CurrentExtension = TargetExtesionRegistry.getExtensionByName(CurrentExtensionName);
        assert(CurrentExtension);
        
        RegistersType CurrentExtensionRegisterTypes = CurrentExtension->getExtensionRegistersType();

        if (RegistersGroups.find(CurrentExtensionRegisterTypes) == RegistersGroups.end()) {
            LOG_INFO_("RegisterFileUnit: initializing register group for extension {}", std::string(CurrentExtensionName));
            RegistersGroups[CurrentExtension->getExtensionRegistersType()].fill(0);
        }
    }
}

void RegisterFileUnit::writeRegister(RegistersType CurrentRegistersType, uint32_t RegisterID, uint32_t Value) {

    assert(RegisterID < REGISTERS_NUMBER);

    if (RegisterID == 0) {
        LOG_INFO_("RegisterFileUnit: ignoring write to zero register (x0)");
        return;
    }

    LOG_INFO_("RegisterFileUnit: writing value 0x{:08X} to register {} of type {}", Value, RegisterID, static_cast<int>(CurrentRegistersType));
    RegistersGroups[CurrentRegistersType][RegisterID] = Value;
}

uint32_t RegisterFileUnit::readRegister(RegistersType CurrentRegistersType, uint32_t RegisterID) {

    LOG_INFO_("RegisterFileUnit: reading register {} of type {}", RegisterID, static_cast<int>(CurrentRegistersType));
    return RegistersGroups[CurrentRegistersType][RegisterID];
}


} // namespace r1scoviy