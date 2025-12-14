#ifndef SRC_SIMULATOR_MEMORY_H
#define SRC_SIMULATOR_MEMORY_H

#include <unordered_map>
#include <array>

const int LEVELS_OF_MEMORY = 2;

const int MINIPAGE_DEFAULT_SIZE = 256;
const int MEMORY_LEVEL_1_SIZE = 8;
const int MEMORY_LEVEL_2_SIZE = 8;

class RAMUnit {
private:
    static_assert(LEVELS_OF_MEMORY == 2,
                  "There should be 32 levels of memory!");
    
    static_assert(MEMORY_LEVEL_1_SIZE == 8,
                  "Memory level 1 size should be equal to 8!");
    static_assert(MEMORY_LEVEL_2_SIZE == 8,
                  "Memory level 2 size should be equal to 8!");

    class Minipage;

    // 32-bit address is splitted to 8-bit on each level
    using std::unordered_map<uint8_t, Minipage> MemoryLevel0;
    using std::unordered_map<uint8_t, MemoryLevel0> MemoryLevel1;
    using std::unordered_map<uint8_t, MemoryLevel1> MemoryLevel2;
    
    MemoryLevel2 Memory;

public:
    void *getMemoryLocation(uint32_t Address);

    uint32_t getMemoryLevel2Offset(uint32_t Address);
    uint32_t getMemoryLevel1Offset(uint32_t Address);

    uint32_t getOffsetInMinipage();

private:
    Minipage &findMinipage(uint32_t Address);
};

class RAMUnit::Minipage {
private:
    static_assert(MINIPAGE_DEFAULT_SIZE == 256,
                  "Minipage default size should be 256!");

    std::optional<std::shared_ptr<char>> MinipageContent;

public:
    void *getMinipageCellAddress(uint32_t Offset);
};

class RAMControllerUnit {
private:    
    std::unique_ptr<RAMUnit> RAM;

public:
    RAMControllerUnit(std::unique_ptr<RAMUnit> &&RAMModule);

    RAMControllerUnit(const RAMController &Other);
    RAMControllerUnit &operator=(const RAMController &Other);

    ~RAMControllerUnit();

    uint8_t  getByte    (uint32_t Address);
    uint16_t getHalfword(uint32_t Address);
    uint32_t getWord    (uint32_t Address);
    
    void storeByte    (uint32_t Address, uint8_t  ByteToStore);
    void storeHalfword(uint32_t Address, uint16_t HalfwordToStore);
    void storeWord    (uint32_t Address, uint32_t WordToStore);
};

#endif