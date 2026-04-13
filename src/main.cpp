#include <memory>

#include "src/Simulator/SPU/SPU.h"
#include "src/Simulator/Memory/Memory.h"
#include "src/Simulator/SPU/ISA/ExtensionRegistry.h"

int main() {
    r1scoviy::RAMUnit Ram;
    r1scoviy::RAMControllerUnit ramController(Ram);
    
    r1scoviy::ExtensionRegistry ExtensionRegistry;
    
    auto spu = std::make_unique<r1scoviy::SPU>(
        std::make_unique<r1scoviy::RAMControllerUnit>(std::move(ramController)),
        ExtensionRegistry
    );
    
    // Start execution from address 0
    spu->start(0);
    
    return 0;
}
