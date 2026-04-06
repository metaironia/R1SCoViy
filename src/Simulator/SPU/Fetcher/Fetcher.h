#ifndef SRC_SIMULATOR_SPU_FETCHER_H
#define SRC_SIMULATOR_SPU_FETCHER_H

#include <cstdint>

namespace r1scoviy {

class FetcherUnit {
public:
    uint32_t fetchNextInstruction();
};

} // namespace r1scoviy

#endif