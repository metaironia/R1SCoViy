#ifndef SRC_SIMULATOR_SPU_ISA_INSTRUCTIONREGISTRY_H
#define SRC_SIMULATOR_SPU_ISA_INSTRUCTIONREGISTRY_H

#include <unordered_map>
#include <memory>

#include "InstructionTypes.h"
#include "ExtensionRegistry.h"
#include "Simulator/SPU/Executor/InstructionDispatcher.h"

namespace r1scoviy {

class InstructionRegistry {
private:
    std::unordered_map<uint32_t, std::shared_ptr<Instruction>> Instructions;

    std::unordered_map<uint32_t, std::shared_ptr<InstructionDispatcher>> OpcodesDispatchers;

public:
    InstructionRegistry(ExtensionRegistry &CurrentExtensionRegistry);

    const std::unordered_map<uint32_t, std::shared_ptr<Instruction>> &getInstructions() const { return Instructions; }
    
    const std::unordered_map<uint32_t, std::shared_ptr<InstructionDispatcher>> &getOpcodesDispatchers() const { return OpcodesDispatchers; }
};

} // namespace r1scoviy

#endif