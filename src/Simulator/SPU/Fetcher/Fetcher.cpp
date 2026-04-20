#include <cassert>

#include "Fetcher.h"

namespace r1scoviy {

uint32_t FetcherUnit::fetchInstruction() {

    return RAMController.getWord(PC);
}

} // namespace r1scoviy
