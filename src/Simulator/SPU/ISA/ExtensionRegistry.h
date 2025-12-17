#ifndef SRC_SIMULATOR_SPU_ISA_EXTENSIONREGISTRY_H
#define SRC_SIMULATOR_SPU_ISA_EXTENSIONREGISTRY_H

class ExtensionRegistry {
private:
    std::unordered_map<std::string, std::unique_ptr<Extension>> RegisteredExtensions;

public:
    template <typename ExtensionName>
    void registerExtension();

    const Extension *getExtensionByName(const std::string &ExtensionName);
};

template <typename ExtensionClassName>
void registerExtension() {

    std::unique_ptr<ExtensionClassName> NewExtension = std::make_unique<ExtensionClassName>();

    RegisteredExtensions[NewExtension.getName()] = std::move(NewExtension);
}

#endif