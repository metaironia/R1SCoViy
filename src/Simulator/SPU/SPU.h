#ifndef SRC_SIMULATOR_SPU_SPU_H
#define SRC_SIMULATOR_SPU_SPU_H

#include <cstdint>
#include <memory>

#include "Simulator/Memory/Memory.h"
#include "Simulator/SPU/Fetcher/Fetcher.h"
#include "Simulator/SPU/Executor/Executor.h"

#include "SPUState.h"

namespace r1scoviy {

class SPU {
private:
    uint32_t PC;    

    FetcherUnit Fetcher;
    ExecutorUnit Executor;

    SpuState State;

public:
    SPU(ExtensionRegistry &ExtensionRegistry, RAMControllerUnit &RAMController);

    ~SPU();

    void start(uint32_t StartInstructionAddress);
};

} // namespace r1scoviy

#endif