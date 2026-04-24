#include <memory>

#include "Simulator/SPU/ISA/RV32I.h"
#include "Simulator/Simulator.h"
#include "Simulator/SPU/ISA/ExtensionRegistry.h"
#include "LogHelper/QuillLogHelper.h"
#include "LogHelper/OverwriteMacros.h"

int main(const int argc, const char *argv[]) {
    SetupQuill("simulator.log");
    
    LOG_INFO_("Simulator starting...");

    r1scoviy::ExtensionRegistry ExtensionRegistry;
    ExtensionRegistry.registerExtension(std::make_shared<r1scoviy::RV32IExtension>());
    
    auto Sim = std::make_unique<r1scoviy::Simulator>(ExtensionRegistry);

    int SimArgc = argc - 1;
    const char **SimArgv = argv + 1;

    Sim->start(SimArgc, SimArgv);
    
    return 0;
}
