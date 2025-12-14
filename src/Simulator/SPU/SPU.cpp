#include "SPU.h"

SPU::SPU(std::unique_ptr<RAMControllerUnit> &&RAMControllerModule)
    : ExecutorUnit(std::move(RAMControllerModule)), CurrentInstructionAddress(0) {}

SPU::SPU(const &SPU Other)
    : RAM(Other.get()) {}

SPU::SPU &operator=(const &SPU Other) {
    
    RAMController.release();
    RAMController.reset(Other.get());

    return *this;
}

SPU::~SPU() {

    RAMController.release();
}

void SPU::start(uint32_t StartInstructionAddress) {

    CurrentInstructionAddress = StartInstructionAddress;

    for (;;) {

        uint32_t CurrInstr = Fetcher.fetchNextInstruction();
                
        Executor.executeInstr(CurrInstr);
    }
}