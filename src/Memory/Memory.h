#ifndef SRC_MEMORY_RAM_H
#define SRC_MEMORY_RAM_H

#include <unordered_map>
#include <array>

const MINIPAGE_DEFAULT_SIZE = 256;
const LEVELS_OF_MEMORY = 2;

class Minipage {
private:
    static_assert(MINIPAGE_DEFAULT_SIZE == 256,
                  "Minipage default size should be 256!");

    bool IsAllocated;
    std::shared_ptr<char> MinipageContent;

public:
    Minipage();

    bool isMinipageAllocated() { return IsAllocated; }

    void *getMinipageCellAddress(uint32_t Offset);

private:
    void AllocateNewMinipage();
};

class RAM {
private:
    static_assert(LEVELS_OF_MEMORY == 2,
                  "There should be 32 levels of memory!");

    // 32-bit address is splitted to 8-bit on each level
    using std::unordered_map<uint8_t, Minipage> MemoryLevel0;
    using std::unordered_map<uint8_t, MemoryLevel0> MemoryLevel1;
    using std::unordered_map<uint8_t, MemoryLevel1> MemoryLevel2;
    
    MemoryLevel2 Memory;

public:
    uint8_t  getByte    (uint32_t Address);
    uint16_t getHalfword(uint32_t Address);
    uint32_t getWord    (uint32_t Address);
    
    void storeByte    (uint32_t Address, uint8_t  ByteToStore);
    void storeHalfword(uint32_t Address, uint16_t HalfwordToStore);
    void storeWord    (uint32_t Address, uint32_t WordToStore);

private:
    Minipage &findMinipage(uint32_t Address);

    uint32_t getMemoryLevel2Offset(uint32_t Address);
    uint32_t getMemoryLevel1Offset(uint32_t Address);

    uint32_t getOffsetInMinipage();
};


#endif