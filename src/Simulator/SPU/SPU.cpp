#include "SPU.h"
#include "Simulator/SPU/Fetcher/Fetcher.h"
#include "LogHelper/OverwriteMacros.h"

namespace r1scoviy {

SPU::SPU(ExtensionRegistry &ExtensionRegistry, RAMControllerUnit &RAMController)
    :  PC(0), Fetcher(RAMController, PC), Executor(ExtensionRegistry, RAMController, PC) {

        LOG_DEBUG_("SPU constructor called");
}

SPU::~SPU() {
    LOG_DEBUG_("SPU destructor called");
}

void SPU::start(uint32_t StartInstructionAddress) {

    LOG_INFO_("SPU starting execution from address: 0x{:08X}", StartInstructionAddress);
    
    PC = StartInstructionAddress;

    for (;;) {

        uint32_t CurrInstr = Fetcher.fetchInstruction();
        
        LOG_INFO_("Fetched instruction: 0x{:08X} at PC: 0x{:08X}", CurrInstr, PC);
                
        Executor.executeInstr(CurrInstr);
    }
}

} // namespace r1scoviy