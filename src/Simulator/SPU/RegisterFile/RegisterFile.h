#ifndef SRC_SIMULATOR_SPU_REGISTERFILE_REGISTERFILE_H
#define SRC_SIMULATOR_SPU_REGISTERFILE_REGISTERFILE_H

#include <unordered_map>
#include <cstdint>
#include <array>

namespace r1scoviy {
class ExtensionRegistry;

enum class RegistersType {

    INTEGER_REGS,
    FLOAT_REGS
};

const int REGISTERS_NUMBER = 32;
const int STACK_POINTER_REG_NUM = 2;

class RegisterFileUnit {
private:
    using Registers = std::array<int32_t, REGISTERS_NUMBER>;     

    std::unordered_map<RegistersType, Registers> RegistersGroups;

public:
    RegisterFileUnit(r1scoviy::ExtensionRegistry &TargetExtesionRegistry);

    void writeRegister(RegistersType CurrentRegistersType, int RegisterID, int32_t Value);

    int32_t readRegister(RegistersType CurrentRegistersType, int RegisterID);
};

} // namespace r1scoviy

#endif