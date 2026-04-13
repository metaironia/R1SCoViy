#include "SPU.h"
#include "src/Simulator/SPU/Fetcher/Fetcher.h"

namespace r1scoviy {

SPU::SPU(std::unique_ptr<RAMControllerUnit> &&RAMControllerModule, ExtensionRegistry &ExtensionRegistry)
    :  PC(0), Fetcher(PC), Executor(*RAMControllerModule->getRAM(), ExtensionRegistry, PC) {}

SPU::~SPU() = default;

void SPU::start(uint32_t StartInstructionAddress) {

    PC = StartInstructionAddress;

    for (;;) {

        uint32_t CurrInstr = Fetcher.fetchNextInstruction();
                
        Executor.executeInstr(CurrInstr);
    }
}

} // namespace r1scoviy