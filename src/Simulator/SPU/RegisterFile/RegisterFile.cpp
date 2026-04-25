#include <vector>
#include <string_view>
#include <cassert>
#include <array>

#include "RegisterFile.h"
#include "Simulator/SPU/ISA/ExtensionRegistry.h"
#include "LogHelper/OverwriteMacros.h"
#include "Simulator/Simulator.h"

namespace r1scoviy {

RegisterFileUnit::RegisterFileUnit(r1scoviy::ExtensionRegistry &TargetExtesionRegistry)
    : RegistersGroups() {

    LOG_DEBUG_("RegisterFileUnit constructor called");

    const auto &RegisteredExtensions = TargetExtesionRegistry.getRegisteredExtensions();

    for (const auto &CurrentExtensionIt: RegisteredExtensions) {

        const auto &CurrentExtension = CurrentExtensionIt.second;

        assert(CurrentExtension);
        
        RegistersType CurrentExtensionRegisterTypes = CurrentExtension->getExtensionRegistersType();

        if (RegistersGroups.find(CurrentExtensionRegisterTypes) == RegistersGroups.end()) {
            
            LOG_DEBUG_("RegisterFileUnit: initializing register group for extension {}", std::string(CurrentExtension->getName()));
            RegistersGroups[CurrentExtensionRegisterTypes].fill(0);
        
            if (CurrentExtensionRegisterTypes == RegistersType::INTEGER_REGS) 
                RegistersGroups[CurrentExtensionRegisterTypes][STACK_POINTER_REG_NUM] = static_cast<int32_t>(StackVirtualAddress);
        }
    }
}

void RegisterFileUnit::writeRegister(RegistersType CurrentRegistersType, int RegisterID, int32_t Value) {

    assert(RegisterID < REGISTERS_NUMBER);

    if (RegisterID == 0) {
        
        LOG_DEBUG_("RegisterFileUnit: ignoring write to zero register (x0)");
        return;
    }

    LOG_DEBUG_("RegisterFileUnit: writing value 0x{:08X} to register {} of type {}", Value, RegisterID, static_cast<int>(CurrentRegistersType));
    RegistersGroups[CurrentRegistersType][RegisterID] = Value;
}

int32_t RegisterFileUnit::readRegister(RegistersType CurrentRegistersType, int RegisterID) {

    LOG_DEBUG_("RegisterFileUnit: reading register {} of type {}", RegisterID, static_cast<int>(CurrentRegistersType));
    return RegistersGroups[CurrentRegistersType][RegisterID];
}


} // namespace r1scoviy