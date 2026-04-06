#include "SPU.h"

namespace r1scoviy {

SPU::SPU(std::unique_ptr<RAMControllerUnit>&& RAMControllerModule, ExtensionRegistry& extensionRegistry)
    : Executor(*RAMControllerModule->getRAM(), extensionRegistry), CurrentInstructionAddress(0) {}

SPU::~SPU() = default;

void SPU::start(uint32_t StartInstructionAddress) {

    CurrentInstructionAddress = StartInstructionAddress;

    for (;;) {

        uint32_t CurrInstr = Fetcher.fetchNextInstruction();
                
        Executor.executeInstr(CurrInstr);
    }
}

} // namespace r1scoviy