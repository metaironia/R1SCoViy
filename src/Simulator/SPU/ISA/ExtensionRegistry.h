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
    ExtensionRegistry();

    void registerExtension(std::shared_ptr<Extension> NewExtension);

    const std::vector<std::string_view> &getRegisteredExtensionsNames() const;
    const Extension *getExtensionByName(const std::string_view ExtensionName) const;
};

} // namespace r1scoviy

#endif