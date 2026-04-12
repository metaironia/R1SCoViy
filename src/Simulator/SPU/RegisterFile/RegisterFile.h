#ifndef SRC_SIMULATOR_SPU_REGISTERFILE_REGISTERFILE_H
#define SRC_SIMULATOR_SPU_REGISTERFILE_REGISTERFILE_H

#include <unordered_map>
#include <string_view>
#include <cstdint>
#include <array>

namespace r1scoviy {
class ExtensionRegistry;

enum class RegistersType {

    INTEGER_REGS,
    FLOAT_REGS
};

const int REGISTERS_NUMBER = 32;

class RegisterFileUnit {
private:
    using Registers = std::array<uint32_t, REGISTERS_NUMBER>;     

    std::unordered_map<RegistersType, Registers> RegistersGroups;

public:
    RegisterFileUnit(r1scoviy::ExtensionRegistry &TargetExtesionRegistry);

    void writeRegister(RegistersType CurrentRegistersType, uint32_t RegisterID, uint32_t Value);

    uint32_t readRegister(RegistersType CurrentRegistersType, uint32_t RegisterID);
};

} // namespace r1scoviy

#endif