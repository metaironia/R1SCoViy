#include <memory>

#include "src/Simulator/SPU/SPU.h"
#include "src/Simulator/Memory/Memory.h"
#include "src/Simulator/SPU/ISA/ExtensionRegistry.h"

int main() {
    // Create RAM unit and controller
    r1scoviy::RAMUnit ram;
    r1scoviy::RAMControllerUnit ramController(ram);
    
    // Create extension registry
    r1scoviy::ExtensionRegistry extensionRegistry;
    
    // Create SPU with unique_ptr to RAM controller
    auto spu = std::make_unique<r1scoviy::SPU>(
        std::make_unique<r1scoviy::RAMControllerUnit>(std::move(ramController)),
        extensionRegistry
    );
    
    // Start execution from address 0
    spu->start(0);
    
    return 0;
}
