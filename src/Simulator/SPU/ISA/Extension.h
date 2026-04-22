#ifndef SRC_SIMULATOR_SPU_ISA_EXTENSION_H
#define SRC_SIMULATOR_SPU_ISA_EXTENSION_H

#include <string_view>
#include <memory>

#include "Simulator/SPU/RegisterFile/RegisterFile.h"
#include "InstructionTypes.h"

namespace r1scoviy {

class Extension {
private:
    std::unordered_map<uint32_t, std::shared_ptr<Instruction>> Instructions;
    RegistersType ExtensionRegistersType;

public:
    virtual const std::string_view getName() const = 0;

    const std::unordered_map<uint32_t, std::shared_ptr<Instruction>> &getInstructions() const;
    
    const RegistersType &getExtensionRegistersType() const;

    void dump() const;

protected:
    Extension()
        : Instructions(), ExtensionRegistersType() {}
    
    void addNewInstr(std::shared_ptr<Instruction> NewInstruction);

public:
    virtual ~Extension() = default;

    virtual void registerInstructions() = 0;
};

} // namespace r1scoviy

#endif