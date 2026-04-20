#include "elfio/elfio.hpp"

#include "LogHelper/OverwriteMacros.h"
#include "Simulator/Simulator.h"

namespace r1scoviy {

bool Simulator::loadFile(const std::string &Filepath) {

    ELFIO::elfio Reader;

    if (!Reader.load(Filepath)) {
       
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

    initRAM(Reader)

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
        size_t SegmentVirtualAddress = CurrSegment->get_virtual_address();  

        for (size_t j = 0; j < SegmentRawSize; j++)
            RAMController.storeByte(SegmentVirtualAddress + j, SegmentRawData[j]);
    }
}

} // namespace r1scoviy