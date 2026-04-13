#ifndef SRC_SIMULATOR_SPU_SPU_H
#define SRC_SIMULATOR_SPU_SPU_H

#include <cstdint>
#include <memory>

#include "src/Simulator/Memory/Memory.h"
#include "src/Simulator/SPU/Fetcher/Fetcher.h"
#include "src/Simulator/SPU/Executor/Executor.h"

namespace r1scoviy {

class SPU {
private:
    uint32_t PC;    

    FetcherUnit Fetcher;
    ExecutorUnit Executor;

public:
    SPU(ExtensionRegistry &ExtensionRegistry);

    ~SPU();

    void start(uint32_t StartInstructionAddress);
};

} // namespace r1scoviy

#endif