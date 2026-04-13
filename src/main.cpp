#include <memory>

#include "src/Simulator/SPU/SPU.h"
#include "src/Simulator/Memory/Memory.h"
#include "src/Simulator/SPU/ISA/ExtensionRegistry.h"

int main() {
    r1scoviy::ExtensionRegistry ExtensionRegistry;
    
    auto Spu = std::make_unique<r1scoviy::SPU>(ExtensionRegistry);
    
    // Start execution from address 0
    Spu->start(0);
    
    return 0;
}
