#ifndef SRC_SIMULATOR_SPU_ISA_EXTENSIONREGISTRY_H
#define SRC_SIMULATOR_SPU_ISA_EXTENSIONREGISTRY_H

#include <unordered_map>
#include <vector>
#include <memory>
#include <string_view>

#include "Extension.h"

namespace r1scoviy {

class ExtensionRegistry {
private:
    std::unordered_map<std::string_view, std::unique_ptr<Extension>> RegisteredExtensions;
    std::vector<std::string_view> RegisteredExtensionsNames;

public:
    template <typename ExtensionName>
    void registerExtension();

    const std::vector<std::string_view> &getRegisteredExtensionsNames() const;
    const Extension *getExtensionByName(const std::string_view ExtensionName) const;
};

template <typename ExtensionClassName>
void ExtensionRegistry::registerExtension() {

    std::unique_ptr<ExtensionClassName> NewExtension = std::make_unique<ExtensionClassName>();
    std::string_view NewExtensionName = NewExtension.getName(); 

    RegisteredExtensionsNames.push_back(NewExtensionName);
    RegisteredExtensions[NewExtensionName] = std::move(NewExtension);
}

} // namespace r1scoviy

#endif