#include "SPU.h"
#include "src/Simulator/SPU/Fetcher/Fetcher.h"

namespace r1scoviy {

SPU::SPU(std::unique_ptr<RAMControllerUnit>&& RAMControllerModule, ExtensionRegistry& ExtensionRegistry)
    : Executor(*RAMControllerModule->getRAM(), ExtensionRegistry, &PC),
      Fetcher(&PC), PC(0) {}

SPU::~SPU() = default;

void SPU::start(uint32_t StartInstructionAddress) {

    PC = StartInstructionAddress;

    for (;;) {

        uint32_t CurrInstr = Fetcher.fetchNextInstruction();
                
        Executor.executeInstr(CurrInstr);
    }
}

} // namespace r1scoviy