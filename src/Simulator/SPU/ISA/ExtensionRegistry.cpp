#include <string_view>

#include "ExtensionRegistry.h"

namespace r1scoviy {

const Extension *ExtensionRegistry::getExtensionByName(const std::string_view ExtensionName) const {

    auto ExtensionIt = RegisteredExtensions.find(ExtensionName);

    return (ExtensionIt != RegisteredExtensions.end())
               ? ExtensionIt->second.get()
               : nullptr;
}

const std::vector<std::string_view> &ExtensionRegistry::getRegisteredExtensionsNames() const {

    return RegisteredExtensionsNames;
}

} // namespace r1scoviy

