#ifndef SRC_SIMULATOR_SPU_ISA_INSTRUCTIONREGISTRY_H
#define SRC_SIMULATOR_SPU_ISA_INSTRUCTIONREGISTRY_H

#include <unordered_map>
#include <memory>
#include <string_view>

#include "InstructionTypes.h"
#include "ExtensionRegistry.h"
#include "ISA.h"

namespace r1scoviy {

class InstructionRegistry {
private:
    std::unordered_map<int, std::shared_ptr<Instruction>> Instructions;

public:
    InstructionRegistry();

    void registerInstrs(ExtensionRegistry &CurrentExtensionRegistry,
                        std::initializer_list<std::string_view> ExtensionsNames);
};

} // namespace r1scoviy

#endif