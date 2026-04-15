#include <memory>

#include "Simulator/SPU/SPU.h"
#include "Simulator/Memory/Memory.h"
#include "Simulator/SPU/ISA/ExtensionRegistry.h"
#include "LogHelper/QuillLogHelper.h"
#include "LogHelper/OverwriteMacros.h"

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
