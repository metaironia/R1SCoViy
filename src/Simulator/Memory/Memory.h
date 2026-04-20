#ifndef SRC_SIMULATOR_MEMORY_H
#define SRC_SIMULATOR_MEMORY_H

#include <cstdint>
#include <unordered_map>
#include <memory>
#include <optional>
#include <cassert>

const int LEVELS_OF_MEMORY = 2;

const int MINIPAGE_BITS_IN_OFFSET = 8;
const int MEMORY_LEVEL_0_BITS_IN_OFFSET = 8;
const int MEMORY_LEVEL_1_BITS_IN_OFFSET = 8;
const int MEMORY_LEVEL_2_BITS_IN_OFFSET = 8;

const int MINIPAGE_MAX_OFFSET = 2 << MINIPAGE_BITS_IN_OFFSET;

namespace r1scoviy {

class RAMUnit {
private:
    static_assert(LEVELS_OF_MEMORY == 2,
                  "There should be 32 levels of memory!");

    static_assert(MEMORY_LEVEL_0_BITS_IN_OFFSET == 8,
                  "Bit width of offset in memory level 0 should be equal to 8!");
    static_assert(MEMORY_LEVEL_1_BITS_IN_OFFSET == 8,
                  "Bit width of offset in memory level 1 should be equal to 8!");
    static_assert(MEMORY_LEVEL_2_BITS_IN_OFFSET == 8,
                  "Bit width of offset in memory level 2 should be equal to 8!");

    class Minipage;

    // 32-bit address is splitted to 8-bit on each level
    using MemoryLevel0 = std::unordered_map<uint32_t, Minipage>;
    using MemoryLevel1 = std::unordered_map<uint32_t, MemoryLevel0>;
    using MemoryLevel2 = std::unordered_map<uint32_t, MemoryLevel1>;
    
    MemoryLevel2 Memory;

public:
    RAMUnit()
        : Memory() {};

    void *getMemoryLocation(uint32_t Address);

    uint32_t getMemoryLevel2Offset(uint32_t Address);
    uint32_t getMemoryLevel1Offset(uint32_t Address);
    uint32_t getMemoryLevel0Offset(uint32_t Address);

    uint32_t getOffsetInMinipage(uint32_t Address);

private:
    uint32_t extractBitsFromAddress(uint32_t Address, unsigned StartBit, unsigned EndBit);

    Minipage &findMinipage(uint32_t Address);

    template <class MemoryHashMapT>
    MemoryHashMapT &findNextMemoryHashMap(std::unordered_map<uint32_t, MemoryHashMapT>& CurrMemoryLevelHashMap,
                                          uint32_t CurrMemoryLevelOffset);
};

class RAMUnit::Minipage {
private:
    static_assert(MINIPAGE_BITS_IN_OFFSET == 8,
                  "Bit width of offset in minipage should be 256!");

    std::optional<std::shared_ptr<char[]>> MinipageContent;

public:
    Minipage()
        : MinipageContent() {};

    void *getMinipageCellAddress(uint32_t Offset);
};

class RAMControllerUnit {
private:    
    std::unique_ptr<RAMUnit> RAM;

public:
    RAMControllerUnit()
        : RAM(std::make_unique<RAMUnit>()) {};

    uint8_t  getByte      (uint32_t Address);
    uint16_t getWord      (uint32_t Address);
    uint32_t getDoubleWord(uint32_t Address);
    
    void storeByte      (uint32_t Address, uint8_t  ByteToStore);
    void storeWord      (uint32_t Address, uint16_t WordToStore);
    void storeDoubleWord(uint32_t Address, uint32_t DoubleWordToStore);
};

template <class MemoryHashMapT>
MemoryHashMapT &RAMUnit::findNextMemoryHashMap(std::unordered_map<uint32_t, MemoryHashMapT>& CurrMemoryLevelHashMap,
                                               uint32_t CurrMemoryLevelOffset) {

    auto NextMemoryLevelHashMapIt = CurrMemoryLevelHashMap.find(CurrMemoryLevelOffset);

    if (NextMemoryLevelHashMapIt == CurrMemoryLevelHashMap.end()) {

        auto InsertResult = CurrMemoryLevelHashMap.try_emplace(CurrMemoryLevelOffset);
        
        NextMemoryLevelHashMapIt = InsertResult.first;
    }

    return NextMemoryLevelHashMapIt->second;
}

} // namespace r1scoviy

#endif