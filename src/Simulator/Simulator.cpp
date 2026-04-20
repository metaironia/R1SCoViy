#include <string_view>

#include <elfio/elfio.hpp>

#include "LogHelper/OverwriteMacros.h"
#include "Simulator/Simulator.h"

namespace r1scoviy {


void Simulator::start(const std::string_view Filepath) {

    ELFIO::elfio Reader;

    loadFile(Reader, Filepath);

    initRAM(Reader);

    uint32_t EntryAddress = Reader.get_entry();

    Processor.start(EntryAddress);
}

bool Simulator::loadFile(ELFIO::elfio &Reader, const std::string_view Filepath) {

    if (!Reader.load(std::string(Filepath))) {
       
        LOG_ERROR_("Failed to load ELF: {}\n", Filepath);
        return false;
    }

    // Validate architecture & class for riscv64-unknown-elf
    if (Reader.get_machine() != ELFIO::EM_RISCV) {
        
        LOG_ERROR_("Not a RISC-V ELF. Machine=0x{:X}\n", Reader.get_machine());
        return false;
    }

    if (Reader.get_class() != ELFIO::ELFCLASS32) {
        
        LOG_ERROR_("ELF is not 64-bit.\n");
        return false;
    }

    return true;
}

void Simulator::initRAM(const ELFIO::elfio &Reader) {

    size_t NumOfSegments = Reader.segments.size();

    for (size_t i = 0; i < NumOfSegments; i++) {
        
        const auto *CurrSegment = Reader.segments[i];
        if (!CurrSegment)
            continue; 

        const char* SegmentRawData = CurrSegment->get_data();
        size_t SegmentRawSize = CurrSegment->get_memory_size();
        uint32_t SegmentVirtualAddress = CurrSegment->get_virtual_address();  

        for (uint32_t j = 0; j < SegmentRawSize; j++)
            RAMController.storeByte(SegmentVirtualAddress + j, SegmentRawData[j]);
    }
}

} // namespace r1scoviy