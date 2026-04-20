#include <memory>

#include "Simulator/Simulator.h"
#include "Simulator/SPU/ISA/ExtensionRegistry.h"
#include "LogHelper/QuillLogHelper.h"
#include "LogHelper/OverwriteMacros.h"

int main() {
    SetupQuill("simulator.log");
    
    LOG_INFO_("Simulator starting...");
    
    r1scoviy::ExtensionRegistry ExtensionRegistry;
    
    auto Sim = std::make_unique<r1scoviy::Simulator>(ExtensionRegistry);

    Sim->start("test.txt");
    
    return 0;
}
