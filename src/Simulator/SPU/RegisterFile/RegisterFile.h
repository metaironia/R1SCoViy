#ifndef SRC_SIMULATOR_SPU_REGISTERFILE_REGISTERFILE_H
#define SRC_SIMULATOR_SPU_REGISTERFILE_REGISTERFILE_H

#include <unordered_map>
#include <string_view>
#include <cstdint>
#include <array>

namespace r1scoviy {
class ExtensionRegistry;
}

using Register_t = uint32_t;
using RegisterID_t = int;

const int REGISTERS_NUMBER = 32;

enum class RegistersType {

    INTEGER_REGS,
    FLOAT_REGS
};

class RegisterFileUnit {
private:
    using Registers = std::array<Register_t, REGISTERS_NUMBER>;     

    std::unordered_map<RegistersType, Registers> RegistersGroups;

public:
    RegisterFileUnit(r1scoviy::ExtensionRegistry &TargetExtesionRegistry);

    Register_t &getReg(RegistersType CurrentRegistersType, RegisterID_t RegisterID);
};

#endif