#include "Memory.h"

Minipage::Minipage() : Minipage(nullptr), IsAllocated(false) {}

void *Minipage::getMinipageCellAddress(uint32_t Offset) {

    if (!isMinipageAllocated)
        AllocateNewMinipage();

    return MinipageContent.get() + Offset;
}

void Minipage::AllocateNewMinipage() {

    if (!MinipageContent)
        MinipageContent = std::make_shared<char>(MINIPAGE_DEFAULT_SIZE);
    else
        return;
        // Trying to allocate already allocated minipage!

    IsAllocated = true;
    IsResponsibleForDestruction = true;
}

void* RAM::getMemoryLocation(uint32_t Address) {

    const shared_ptr<Minipage> FoundMinipage = findMinipage(Address);

    uint32_t OffsetInMinipage = getOffsetInMinipage(Address);

    void *MemoryLocation = FoundMinipage.getMinipageCellAddress(OffsetInMinipage);
    assert(MemoryLocation);

    return MemoryLocation;
}

template <class MemoryHashMapT>
MemoryHashMapT &findNextMemoryHashMap(std::unordered_map<uint32_t, MemoryHashMapT> CurrMemoryLevelHashMap,
                                      uint32_t CurrMemoryLevelOffset) {

    auto NextMemoryLevelHashMapIt = CurrMemoryLevelHashMap.find(CurrMemoryLevelOffset);

    if (NextMemoryLevelHashMapIt == CurrMemoryLevelHashMap.end()) {

        auto InsertResult = CurrMemoryLevelHashMap.insert(CurrMemoryLevelOffset,
                                                          std::unordered_map());
        
        NextMemoryLevelHashMapIt = InsertResult.first;

        bool IsNewHashMapInserted = InsertResult.second;
        assert(IsNewHashMapInserted);
    }

    return *NextMemoryLevelHashMapIt;
}

Minipage &RAM::findMinipage(uint32_t Address) {

    MemoryLevel1 &CurrentMemoryLevel1HashMap = 
            findNextMemoryHashMap<MemoryLevel1>(Memory, 
                                                getMemoryLevel2Offset(Address));

    MemoryLevel0 &CurrentMemoryLevel0HashMap = 
            findNextMemoryHashMap<MemoryLevel0>(CurrentMemoryLevel1HashMap, 
                                                getMemoryLevel1Offset(Address));  

    uint32_t MemoryLevel0Offset = getMemoryLevel0Offset(Address);

    auto MinipageIt = CurrentMemoryLevel0HashMap.find(MemoryLevel0Offset);
    if (MinipageIt == CurrentMemoryLevel0HashMap.end())
        CurrentMemoryLevel0HashMap.insert(MemoryLevel0Offset, Minipage());

    return *MinipageIt;
}

uint32_t RAM::getOffsetInMinipage(uint32_t Address) {

    return Address % MINIPAGE_DEFAULT_SIZE;
}

uint8_t RAM::getByte(uint32_t Address) {
    
    void *MemoryLocation = getMemoryLocation(Address);
    assert(MemoryLocation);

    return *(static_cast<uint8_t *>(MemoryLocation));
}

uint16_t RAM::getHalfword(uint32_t Address) {
    
    void *MemoryLocation = getMemoryLocation(Address);
    assert(MemoryLocation);

    return *(static_cast<uint16_t *>(MemoryLocation));
}

uint32_t RAM::getWord(uint32_t Address) {
    
    void *MemoryLocation = getMemoryLocation(Address);
    assert(MemoryLocation);

    return *(static_cast<uint32_t *>(MemoryLocation));
}
    
void RAM::storeByte(uint32_t Address, uint8_t ByteToStore) {

    void *MemoryLocation = getMemoryLocation(Address);
    assert(MemoryLocation);

    *(static_cast<uint8_t *>(MemoryLocation)) = ByteToStore;
}

void RAM::storeHalfword(uint32_t Address, uint16_t HalfwordToStore) {

    void *MemoryLocation = getMemoryLocation(Address);
    assert(MemoryLocation);

    *(static_cast<uint16_t *>(MemoryLocation)) = HalfwordToStore;
}

void RAM::storeWord(uint32_t Address, uint32_t WordToStore) {

    void *MemoryLocation = getMemoryLocation(Address);
    assert(MemoryLocation);

    *(static_cast<uint8_t *>(MemoryLocation)) = HalfwordToStore;
}