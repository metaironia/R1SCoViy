#include "Memory.h"

RAMControllerUnit::RAMControllerUnit(std::unique_ptr<RAMUnit> &&RAMModule) 
    : RAM(std::move(RAMModule)) {}

RAMControllerUnit::RAMControllerUnit(const RAMController &Other)
    : RAM(Other.get()) {}

RAMControllerUnit::RAMControllerUnit &operator=(const RAMController &Other) {

    RAM.release();
    RAM.reset(Other.get());

    return *this;
}
    
RAMControllerUnit::~RAMControllerUnit() {

    RAM.release();
}

void *RAMUnit::Minipage::getMinipageCellAddress(uint32_t Offset) {

    if (!MinipageContent.has_value())
        MinipageContent.emplace(MINIPAGE_DEFAULT_SIZE);

    return MinipageContent->get() + Offset;
}

void *RAMUnit::getMemoryLocation(uint32_t Address) {

    const shared_ptr<Minipage> FoundMinipage = findMinipage(Address);

    uint32_t OffsetInMinipage = getOffsetInMinipage(Address);

    void *MemoryLocation = FoundMinipage.getMinipageCellAddress(OffsetInMinipage);
    assert(MemoryLocation);

    return MemoryLocation;
}

template <class MemoryHashMapT>
MemoryHashMapT &RAMUnit::findNextMemoryHashMap(std::unordered_map<uint32_t, MemoryHashMapT> CurrMemoryLevelHashMap,
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

Minipage &RAMUnit::findMinipage(uint32_t Address) {

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

uint32_t RAMUnit::getOffsetInMinipage(uint32_t Address) {

    return Address % MINIPAGE_DEFAULT_SIZE;
}

uint32_t getMemoryLevel1Offset(uint32_t Address) {

    return Address % MEMORY_LEVEL_1_SIZE;
}

uint32_t getMemoryLevel2Offset(uint32_t Address) {

    return Address % MEMORY_LEVEL_2_SIZE;
}

uint8_t RAMControllerUnit::getByte(uint32_t Address) {
    
    void *MemoryLocation = getMemoryLocation(Address);
    assert(MemoryLocation);

    return *(static_cast<uint8_t *>(MemoryLocation));
}

uint16_t RAMControllerUnit::getHalfword(uint32_t Address) {
    
    void *MemoryLocation = getMemoryLocation(Address);
    assert(MemoryLocation);

    return *(static_cast<uint16_t *>(MemoryLocation));
}

uint32_t RAMControllerUnit::getWord(uint32_t Address) {
    
    void *MemoryLocation = getMemoryLocation(Address);
    assert(MemoryLocation);

    return *(static_cast<uint32_t *>(MemoryLocation));
}
    
void RAMControllerUnit::storeByte(uint32_t Address, uint8_t ByteToStore) {

    void *MemoryLocation = getMemoryLocation(Address);
    assert(MemoryLocation);

    *(static_cast<uint8_t *>(MemoryLocation)) = ByteToStore;
}

void RAMControllerUnit::storeHalfword(uint32_t Address, uint16_t HalfwordToStore) {

    void *MemoryLocation = getMemoryLocation(Address);
    assert(MemoryLocation);

    *(static_cast<uint16_t *>(MemoryLocation)) = HalfwordToStore;
}

void RAMControllerUnit::storeWord(uint32_t Address, uint32_t WordToStore) {

    void *MemoryLocation = getMemoryLocation(Address);
    assert(MemoryLocation);

    *(static_cast<uint8_t *>(MemoryLocation)) = HalfwordToStore;
}