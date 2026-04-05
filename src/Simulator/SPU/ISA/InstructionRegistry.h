#ifndef SRC_SIMULATOR_SPU_ISA_INSTRUCTIONREGISTRY_H
#define SRC_SIMULATOR_SPU_ISA_INSTRUCTIONREGISTRY_H

#include <unordered_map>
#include <memory>
#include <string_view>

#include "InstructionTypes.h"
#include "ExtensionRegistry.h"
#include "src/Simulator/SPU/Executor/InstructionDispatcher.h"

namespace r1scoviy {

class InstructionRegistry {
private:
    std::unordered_map<uint32_t, std::shared_ptr<Instruction>> Instructions;

    std::unordered_map<uint32_t, std::shared_ptr<InstructionDispatcher>> OpcodesDispatchers;

public:
    InstructionRegistry();

    const std::unordered_map<uint32_t, std::shared_ptr<Instruction>>& getInstructions() const { return Instructions; }
    
    const std::unordered_map<uint32_t, std::shared_ptr<InstructionDispatcher>>& getOpcodesDispatchers() const { return OpcodesDispatchers; }

    void registerInstrs(ExtensionRegistry &CurrentExtensionRegistry,
                        std::initializer_list<std::string_view> ExtensionsNames);
};

} // namespace r1scoviy

#endif