#include <cassert>

#include "Fetcher.h"

namespace r1scoviy {

uint32_t FetcherUnit::fetchInstruction() {

    return RAMController.loadWord(PC);
}

} // namespace r1scoviy
