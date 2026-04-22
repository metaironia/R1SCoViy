#include <string_view>
#include <cassert>

#include "ExtensionRegistry.h"

namespace r1scoviy {

void ExtensionRegistry::registerExtension(std::shared_ptr<Extension> NewExtension) {

    assert(NewExtension);

    NewExtension->registerInstructions();

    std::string_view NewExtensionName = NewExtension->getName(); 

    RegisteredExtensionsNames.push_back(NewExtensionName);
    RegisteredExtensions[NewExtensionName] = NewExtension;
}

const Extension *ExtensionRegistry::getExtensionByName(const std::string_view ExtensionName) const {

    auto ExtensionIt = RegisteredExtensions.find(ExtensionName);

    return (ExtensionIt != RegisteredExtensions.end())
               ? ExtensionIt->second.get()
               : nullptr;
}

const std::unordered_map<std::string_view, std::shared_ptr<Extension>> &ExtensionRegistry::getRegisteredExtensions() const {

    return RegisteredExtensions;
}

const std::vector<std::string_view> &ExtensionRegistry::getRegisteredExtensionsNames() const {

    return RegisteredExtensionsNames;
}

} // namespace r1scoviy

