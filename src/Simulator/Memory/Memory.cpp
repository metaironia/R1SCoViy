#include <memory>
#include <cassert>

#include "Memory.h"

RAMControllerUnit::RAMControllerUnit(RAMUnit &RAMModule) 
    : RAM(&RAMModule) {}

void *RAMUnit::Minipage::getMinipageCellAddress(uint32_t Offset) {

    if (!MinipageContent.has_value())
        MinipageContent.emplace(std::make_unique<char[]>(MINIPAGE_MAX_OFFSET));

    return MinipageContent->get() + Offset;
}

void *RAMUnit::getMemoryLocation(uint32_t Address) {

    Minipage &FoundMinipage = findMinipage(Address);

    uint32_t OffsetInMinipage = getOffsetInMinipage(Address);

    void *MemoryLocation = FoundMinipage.getMinipageCellAddress(OffsetInMinipage);
    assert(MemoryLocation);

    return MemoryLocation;
}

RAMUnit::Minipage &RAMUnit::findMinipage(uint32_t Address) {

    MemoryLevel1 &MemoryLevel1HashMap = 
            findNextMemoryHashMap<MemoryLevel1>(Memory, 
                                                getMemoryLevel2Offset(Address));

    MemoryLevel0 &MemoryLevel0HashMap = 
            findNextMemoryHashMap<MemoryLevel0>(MemoryLevel1HashMap, 
                                                getMemoryLevel1Offset(Address));  

    uint8_t MemoryLevel0Offset = getMemoryLevel0Offset(Address);

    auto MinipageIt = MemoryLevel0HashMap.find(MemoryLevel0Offset);
    if (MinipageIt == MemoryLevel0HashMap.end())
        MemoryLevel0HashMap[MemoryLevel0Offset] = Minipage();

    return MinipageIt->second;
}

uint32_t RAMUnit::extractBitsFromAddress(uint32_t Address, unsigned StartBit, unsigned EndBit) {

    unsigned LeftShift = sizeof(Address) * 8 - (EndBit + 1);
    unsigned RightShift = StartBit + LeftShift;

    return ((Address << LeftShift) >> RightShift);
}

uint32_t RAMUnit::getOffsetInMinipage(uint32_t Address) {

    unsigned StartBit = 0;
    unsigned EndBit = MINIPAGE_BITS_IN_OFFSET - 1;

    return extractBitsFromAddress(Address, StartBit, EndBit);
}

uint32_t RAMUnit::getMemoryLevel1Offset(uint32_t Address) {

    unsigned StartBit = MINIPAGE_BITS_IN_OFFSET;
    unsigned EndBit = StartBit + MEMORY_LEVEL_0_BITS_IN_OFFSET - 1;

    return extractBitsFromAddress(Address, StartBit, EndBit);
}

uint32_t RAMUnit::getMemoryLevel2Offset(uint32_t Address) {
  
    unsigned StartBit = MINIPAGE_BITS_IN_OFFSET + MEMORY_LEVEL_0_BITS_IN_OFFSET + MEMORY_LEVEL_1_BITS_IN_OFFSET;
    unsigned EndBit = StartBit + MEMORY_LEVEL_2_BITS_IN_OFFSET - 1;

    return extractBitsFromAddress(Address, StartBit, EndBit);
}

uint8_t RAMControllerUnit::getByte(uint32_t Address) {
    
    assert(RAM);

    void *MemoryLocation = RAM->getMemoryLocation(Address);
    assert(MemoryLocation);

    return *(static_cast<uint8_t *>(MemoryLocation));
}

uint16_t RAMControllerUnit::getHalfword(uint32_t Address) {
    
    assert(RAM);

    void *MemoryLocation = RAM->getMemoryLocation(Address);
    assert(MemoryLocation);

    return *(static_cast<uint16_t *>(MemoryLocation));
}

uint32_t RAMControllerUnit::getWord(uint32_t Address) {
    
    assert(RAM);

    void *MemoryLocation = RAM->getMemoryLocation(Address);
    assert(MemoryLocation);

    return *(static_cast<uint32_t *>(MemoryLocation));
}
    
void RAMControllerUnit::storeByte(uint32_t Address, uint8_t ByteToStore) {

    assert(RAM);

    void *MemoryLocation = RAM->getMemoryLocation(Address);
    assert(MemoryLocation);

    *(static_cast<uint8_t *>(MemoryLocation)) = ByteToStore;
}

void RAMControllerUnit::storeHalfword(uint32_t Address, uint16_t HalfwordToStore) {

    assert(RAM);

    void *MemoryLocation = RAM->getMemoryLocation(Address);
    assert(MemoryLocation);

    *(static_cast<uint16_t *>(MemoryLocation)) = HalfwordToStore;
}

void RAMControllerUnit::storeWord(uint32_t Address, uint32_t WordToStore) {

    assert(RAM);

    void *MemoryLocation = RAM->getMemoryLocation(Address);
    assert(MemoryLocation);

    *(static_cast<uint32_t *>(MemoryLocation)) = WordToStore;
}