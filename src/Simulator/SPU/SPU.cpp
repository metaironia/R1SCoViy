#include "SPU.h"
#include "Simulator/SPU/Fetcher/Fetcher.h"
#include "LogHelper/OverwriteMacros.h"

namespace r1scoviy {

SPU::SPU(ExtensionRegistry &ExtensionRegistry)
    :  PC(0), Fetcher(PC), Executor(ExtensionRegistry, PC) {
    LOG_DEBUG_("SPU constructor called");
}

SPU::~SPU() {
    LOG_DEBUG_("SPU destructor called");
}

void SPU::start(uint32_t StartInstructionAddress) {

    LOG_INFO_("SPU starting execution from address: 0x{:08X}", StartInstructionAddress);
    
    PC = StartInstructionAddress;

    for (;;) {

        uint32_t CurrInstr = Fetcher.fetchNextInstruction();
        
        LOG_TRACE_("Fetched instruction: 0x{:08X} at PC: 0x{:08X}", CurrInstr, PC);
                
        Executor.executeInstr(CurrInstr);
    }
}

} // namespace r1scoviy