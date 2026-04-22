#include <cassert>

#include "Fetcher.h"

namespace r1scoviy {

uint32_t FetcherUnit::fetchInstruction() {

    return RAMController.getDoubleWord(PC);
}

} // namespace r1scoviy
