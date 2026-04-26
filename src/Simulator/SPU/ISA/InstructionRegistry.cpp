#include <cassert>
#include <unordered_map>

#include "InstructionRegistry.h"

namespace r1scoviy {

InstructionRegistry::InstructionRegistry(ExtensionRegistry &CurrentExtensionRegistry)
    : Instructions(), OpcodesDispatchers() {

    const auto &RegisteredExtension = CurrentExtensionRegistry.getRegisteredExtensions();

    for (const auto &CurrentExtensionIt: RegisteredExtension) {

        const auto &CurrentExtension = CurrentExtensionIt.second;

        assert(CurrentExtension);

        const auto &InstructionsMap = CurrentExtension->getInstructions();

        for (const auto &CurrInstrIt: InstructionsMap) {

            assert(CurrInstrIt.second);

            Instructions.try_emplace(CurrInstrIt.first, CurrInstrIt.second);
            OpcodesDispatchers.try_emplace(CurrInstrIt.second->getOpcode(), CurrInstrIt.second->getDispatcher());
        }
    }
}

} // namespace r1scoviy