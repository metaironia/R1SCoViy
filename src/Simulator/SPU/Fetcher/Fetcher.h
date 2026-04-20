#ifndef SRC_SIMULATOR_SPU_FETCHER_H
#define SRC_SIMULATOR_SPU_FETCHER_H

#include <cstdint>

#include "Simulator/Memory/Memory.h"

namespace r1scoviy {

class FetcherUnit {
private:
    RAMControllerUnit &RAMController;

    const uint32_t &PC;

public:
    FetcherUnit(RAMControllerUnit &_RAMController, uint32_t &_PC)
        : RAMController(_RAMController), PC(_PC) {}
    
    ~FetcherUnit() = default;

    uint32_t fetchInstruction();
};

} // namespace r1scoviy

#endif // SRC_SIMULATOR_SPU_FETCHER_H
