#ifndef SRC_SIMULATOR_SPU_ISA_EXTENSION_H
#define SRC_SIMULATOR_SPU_ISA_EXTENSION_H

#include <variant>
#include <vector>
#include <string_view>
#include <memory>

#include "src/Simulator/SPU/RegisterFile/RegisterFile.h"
#include "InstructionTypes.h"

class Extension {
private:
    using InstructionPtrVariant = std::variant<std::shared_ptr<NotMemoryTypeInstruction>,
                                               std::shared_ptr<MemoryTypeInstruction>>;

    std::vector<InstructionPtrVariant> ExtensionRelatedInstrs;
    RegistersType ExtensionRegistersType;

public:
    virtual const std::string_view getName() const = 0;

    const std::vector<InstructionPtrVariant> &getExtensionRelatedInstrs() const;
    RegistersType getExtensionRegistersType() const;

protected:
    Extension() = default;
    
    virtual ~Extension() = default;

    template <typename InstructionType>
    void addNewInstr(std::shared_ptr<InstructionType> &NewInstruction);
};

template <typename InstructionType>
void Extension::addNewInstr(std::shared_ptr<InstructionType> &NewInstruction) {

    ExtensionRelatedInstrs.push_back(NewInstruction);
}

#endif