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
    FetcherUnit Fetcher;
    ExecutorUnit Executor;
    uint32_t CurrentInstructionAddress;
    
public:
    explicit SPU(std::unique_ptr<RAMControllerUnit>&& RAMControllerModule, ExtensionRegistry& extensionRegistry);

    SPU(const SPU& Other) = delete;
    SPU& operator=(const SPU& Other) = delete;

    ~SPU();

    void start(uint32_t StartInstructionAddress);
};

} // namespace r1scoviy

#endif