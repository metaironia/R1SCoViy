#include "ExtensionRegistry.h"

const Extension ExtensionRegistry::*getExtensionByName(const std::string &ExtensionName) {

    auto ExtensionIt = RegisteredExtension.find(ExtensionName);

    return (ExtensionIt != RegisteredExtension.end())
               ? ExtensionIt->second.get()
               : nullptr ;
}
