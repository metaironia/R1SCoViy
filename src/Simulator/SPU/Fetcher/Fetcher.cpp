#include <cassert>

#include "LogHelper/OverwriteMacros.h"

#include "Fetcher.h"
#include "ELFParser.h"

namespace r1scoviy {

uint32_t FetcherUnit::fetchInstruction() {

    return RAMController.getWord(PC);
}

} // namespace r1scoviy
