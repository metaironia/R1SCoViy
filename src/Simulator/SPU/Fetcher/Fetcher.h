#ifndef SRC_SIMULATOR_SPU_FETCHER_H
#define SRC_SIMULATOR_SPU_FETCHER_H

#include <cstdint>

namespace r1scoviy {

class FetcherUnit {
private:
    const uint32_t &PC;

public:
    FetcherUnit(uint32_t &_PC)
        : PC(_PC) {}

    uint32_t fetchNextInstruction();
};

} // namespace r1scoviy

#endif