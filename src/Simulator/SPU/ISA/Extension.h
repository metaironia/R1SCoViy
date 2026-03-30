#ifndef SRC_SIMULATOR_SPU_ISA_EXTENSION_H
#define SRC_SIMULATOR_SPU_ISA_EXTENSION_H

#include <string_view>
#include <memory>

#include "src/Simulator/SPU/RegisterFile/RegisterFile.h"
#include "InstructionTypes.h"

namespace r1scoviy {

class Extension {
private:
    std::unordered_map<uint32_t, std::shared_ptr<Instruction>> Instructions;
    RegistersType ExtensionRegistersType;

public:
    virtual const std::string_view getName() const = 0;

    RegistersType getExtensionRegistersType() const;

    void dump() const;

protected:
    Extension() = default;
    
    virtual ~Extension() = default;

    void addNewInstr(std::shared_ptr<Instruction> &NewInstruction);
};

} // namespace r1scoviy

#endif