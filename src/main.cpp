#include <memory>

#include "src/Simulator/SPU/SPU.h"
#include "src/Simulator/Memory/Memory.h"
#include "src/Simulator/SPU/ISA/ExtensionRegistry.h"
#include "src/LogHelper/QuillLogHelper.h"
#include "src/LogHelper/OverwriteMacros.h"

int main() {
    SetupQuill("simulator.log");
    
    LOG_INFO_("Simulator starting...");
    
    r1scoviy::ExtensionRegistry ExtensionRegistry;
    
    auto Spu = std::make_unique<r1scoviy::SPU>(ExtensionRegistry);
    
    LOG_INFO_("SPU initialized, starting execution from address 0");
    
    // Start execution from address 0
    Spu->start(0);
    
    return 0;
}
