#include <cstdint>
#include <string_view>
#include <queue>

#include <elfio/elfio.hpp>

#include "LogHelper/OverwriteMacros.h"
#include "MathHelper/MathHelper.h"
#include "Simulator/Simulator.h"

namespace r1scoviy {


void Simulator::start(int Argc, const char *Argv[]) {

    assert(Argv);

    ELFIO::elfio Reader;

    loadFile(Reader, Argv[0]);

    initRAM(Reader, Argc, Argv);

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

void Simulator::initRAM(const ELFIO::elfio &Reader, int Argc, const char *Argv[]) {

    assert(Argv);

    initCmdArgs(Argc, Argv);

    initSegments(Reader);
}

void Simulator::initCmdArgs(int Argc, const char *Argv[]) {

    assert(Argv);
    assert(Argc > 0);

    uint32_t CurrentCmdArgvByteVirtualAddress = CmdArgvVirtualAddress;

    std::queue<uint32_t> AddressesOfArgvString;

    for (size_t i = 0; i < Argc; i++) {

        AddressesOfArgvString.push(CurrentCmdArgvByteVirtualAddress);

        for (uint32_t j = 0; Argv[i][j] != '\0'; CurrentCmdArgvByteVirtualAddress++, j++)
            RAMController.storeByte(CurrentCmdArgvByteVirtualAddress, static_cast<uint8_t>(Argv[i][j]));
            
        RAMController.storeByte(CurrentCmdArgvByteVirtualAddress++, '\0');
    }

    RAMController.storeWord(StackVirtualAddress, Argc);

    for (size_t i = 0; i < Argc; i++) {

        RAMController.storeWord(StackVirtualAddress + sizeof(uint32_t) + i * 4, AddressesOfArgvString.front());

        AddressesOfArgvString.pop();
    }
}

void Simulator::initSegments(const ELFIO::elfio &Reader) {

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