#include <variant>
#include <string_view>
#include <cassert>
#include <unordered_map>
#include <memory>

#include "InstructionRegistry.h"
#include "InstructionTypes.h"

namespace r1scoviy {

InstructionRegistry::InstructionRegistry() = default;

void InstructionRegistry::registerInstrs(ExtensionRegistry &CurrentExtensionRegistry,
                                         std::initializer_list<std::string_view> ExtensionsNames) {

    for (const auto &CurrentExtensionName: ExtensionsNames) {

        const Extension *CurrentExtension = CurrentExtensionRegistry.getExtensionByName(CurrentExtensionName);
        if (!CurrentExtension) {
            continue; // TODO: log this
        }
    }
}

} // namespace r1scoviy