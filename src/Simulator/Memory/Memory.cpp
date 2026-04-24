#include <memory>
#include <cassert>

#include "Memory.h"
#include "LogHelper/OverwriteMacros.h"

namespace r1scoviy {

void *RAMUnit::Minipage::getMinipageCellAddress(uint32_t Offset) {

    if (!MinipageContent.has_value()) {
        LOG_DEBUG_("Minipage: allocating new minipage at offset {}", Offset);
        MinipageContent.emplace(std::make_unique<char[]>(MINIPAGE_MAX_OFFSET));
    }

    return MinipageContent->get() + Offset;
}

void *RAMUnit::getMemoryLocation(uint32_t Address) {

    LOG_DEBUG_("RAM: getting memory location at address 0x{:08X}", Address);

    Minipage &FoundMinipage = findMinipage(Address);

    uint32_t OffsetInMinipage = getOffsetInMinipage(Address);

    void *MemoryLocation = FoundMinipage.getMinipageCellAddress(OffsetInMinipage);
    assert(MemoryLocation);

    return MemoryLocation;
}

RAMUnit::Minipage &RAMUnit::findMinipage(uint32_t Address) {

    LOG_DEBUG_("RAM: finding minipage for address 0x{:08X}", Address);

    MemoryLevel1 &MemoryLevel1HashMap = 
            findNextMemoryHashMap<MemoryLevel1>(Memory, 
                                                getMemoryLevel2Offset(Address));

    MemoryLevel0 &MemoryLevel0HashMap = 
            findNextMemoryHashMap<MemoryLevel0>(MemoryLevel1HashMap, 
                                                getMemoryLevel1Offset(Address));  

    uint32_t MemoryLevel0Offset = getMemoryLevel0Offset(Address);

    auto MinipageIt = MemoryLevel0HashMap.find(MemoryLevel0Offset);
    if (MinipageIt == MemoryLevel0HashMap.end()) {
        LOG_DEBUG_("RAM: creating new minipage at level 0 offset {}", MemoryLevel0Offset);
        MinipageIt = MemoryLevel0HashMap.try_emplace(MemoryLevel0Offset).first;
    }

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

uint32_t RAMUnit::getMemoryLevel0Offset(uint32_t Address) {

    unsigned StartBit = MINIPAGE_BITS_IN_OFFSET + MEMORY_LEVEL_0_BITS_IN_OFFSET;
    unsigned EndBit = StartBit + MEMORY_LEVEL_1_BITS_IN_OFFSET - 1;

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

uint8_t RAMControllerUnit::loadByte(uint32_t Address) {
    
    LOG_DEBUG_("RAMController: loading byte from address 0x{:08X}", Address);
    
    assert(RAM);

    void *MemoryLocation = RAM->getMemoryLocation(Address);
    assert(MemoryLocation);

    return *(static_cast<uint8_t *>(MemoryLocation));
}

uint16_t RAMControllerUnit::loadHalfWord(uint32_t Address) {
    
    LOG_DEBUG_("RAMController: loading halfword from address 0x{:08X}", Address);
    
    assert(RAM);

    void *MemoryLocation = RAM->getMemoryLocation(Address);
    assert(MemoryLocation);

    return *(static_cast<uint16_t *>(MemoryLocation));
}

uint32_t RAMControllerUnit::loadWord(uint32_t Address) {
    
    LOG_DEBUG_("RAMController: loading word from address 0x{:08X}", Address);
    
    assert(RAM);

    void *MemoryLocation = RAM->getMemoryLocation(Address);
    assert(MemoryLocation);

    return *(static_cast<uint32_t *>(MemoryLocation));
}
    
void RAMControllerUnit::storeByte(uint32_t Address, uint8_t ByteToStore) {

    LOG_DEBUG_("RAMController: storing byte 0x{:02X} at address 0x{:08X}", static_cast<unsigned int>(ByteToStore), Address);

    assert(RAM);

    void *MemoryLocation = RAM->getMemoryLocation(Address);
    assert(MemoryLocation);

    *(static_cast<uint8_t *>(MemoryLocation)) = ByteToStore;
}

void RAMControllerUnit::storeHalfWord(uint32_t Address, uint16_t WordToStore) {

    LOG_DEBUG_("RAMController: storing halfword 0x{:04X} at address 0x{:08X}", static_cast<unsigned int>(WordToStore), Address);

    assert(RAM);

    void *MemoryLocation = RAM->getMemoryLocation(Address);
    assert(MemoryLocation);

    *(static_cast<uint16_t *>(MemoryLocation)) = WordToStore;
}

void RAMControllerUnit::storeWord(uint32_t Address, uint32_t DoubleWordToStore) {

    LOG_DEBUG_("RAMController: storing word 0x{:08X} at address 0x{:08X}", DoubleWordToStore, Address);

    assert(RAM);

    void *MemoryLocation = RAM->getMemoryLocation(Address);
    assert(MemoryLocation);

    *(static_cast<uint32_t *>(MemoryLocation)) = DoubleWordToStore;
}

} // namespace r1scoviy