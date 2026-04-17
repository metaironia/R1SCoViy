#include "ELFParser.h"

#include <elfio/elfio.hpp>
#include <stdexcept>
#include <algorithm>

namespace elf_parser {

std::optional<size_t> TextSection::findInstructionIndexByAddress(uint64_t address) const {
    // Binary search for the instruction with the given address
    auto it = std::lower_bound(
        instructions.begin(),
        instructions.end(),
        address,
        [](const Instruction& instr, uint64_t addr) {
            return instr.address < addr;
        }
    );
    
    if (it != instructions.end() && it->address == address) {
        return it->index;
    }
    return std::nullopt;
}

ELFParser::ELFParser() : elf_reader_(std::make_unique<ELFIO::elfio>()) {}

ELFParser::~ELFParser() = default;

bool ELFParser::loadFile(const std::string& filepath) {
    last_error_.clear();
    text_section_.reset();
    entry_point_ = 0;

    try {
        if (!elf_reader_->load(filepath)) {
            last_error_ = "Failed to load ELF file: " + filepath;
            return false;
        }

        // Verify it's a RISC-V 64-bit ELF file
        if (elf_reader_->get_machine() != ELFIO::EM_RISCV) {
            last_error_ = "Not a RISC-V ELF file";
            return false;
        }

        if (elf_reader_->get_class() != ELFIO::ELFCLASS64) {
            last_error_ = "Not a 64-bit ELF file";
            return false;
        }

        entry_point_ = elf_reader_->get_entry();

        if (!parseTextSection()) {
            return false;
        }

        return true;
    } catch (const std::exception& e) {
        last_error_ = std::string("Exception while loading ELF file: ") + e.what();
        return false;
    }
}

bool ELFParser::parseTextSection() {
    const ELFIO::section* text_sec = elf_reader_->sections[".text"];
    
    if (text_sec == nullptr) {
        last_error_ = ".text section not found in ELF file";
        return false;
    }

    TextSection text_section;
    text_section.name = ".text";
    text_section.base_address = text_sec->get_address();
    
    const ELFIO::Elf_Xword size = text_sec->get_size();
    const char* data = text_sec->get_data();
    
    if (data == nullptr || size == 0) {
        last_error_ = ".text section has no data";
        return false;
    }

    // RISC-V instructions are either 16-bit (compressed) or 32-bit (standard)
    // We'll read them as 32-bit values, handling compressed instructions
    size_t instruction_count = 0;
    ELFIO::Elf64_Addr current_addr = text_section.base_address;
    
    while (instruction_count * sizeof(uint32_t) <= static_cast<size_t>(size)) {
        size_t offset = instruction_count * sizeof(uint32_t);
        
        if (offset + sizeof(uint32_t) > static_cast<size_t>(size)) {
            // Handle potential 16-bit compressed instruction at the end
            if (offset + sizeof(uint16_t) <= static_cast<size_t>(size)) {
                uint16_t compressed_instr;
                std::memcpy(&compressed_instr, data + offset, sizeof(uint16_t));
                
                Instruction instr;
                instr.address = current_addr;
                instr.binary_code = static_cast<uint32_t>(compressed_instr);
                instr.index = text_section.instructions.size();
                text_section.instructions.push_back(instr);
            }
            break;
        }
        
        uint32_t instruction_word;
        std::memcpy(&instruction_word, data + offset, sizeof(uint32_t));
        
        Instruction instr;
        instr.address = current_addr;
        instr.binary_code = instruction_word;
        instr.index = text_section.instructions.size();
        text_section.instructions.push_back(instr);
        
        // Determine instruction size based on the two least significant bits
        // Compressed instructions have opcode bits [1:0] != 11 (i.e., not 0b11)
        uint8_t opcode_low2 = instruction_word & 0x3;
        size_t instr_size = (opcode_low2 == 0x3) ? 4 : 2;  // 32-bit or 16-bit
        
        current_addr += instr_size;
        
        // For our simple model, we still increment by 4 bytes in the data array
        // since we're reading 32-bit words, but track the actual address separately
        if (instr_size == 2) {
            // Compressed instruction - we've already read it as part of a 32-bit word
            // Need to handle the next 16-bit half if it exists
            if (offset + sizeof(uint32_t) <= static_cast<size_t>(size)) {
                uint16_t second_half = instruction_word >> 16;
                if ((second_half & 0x3) != 0x3) {
                    // Second half is also compressed
                    Instruction instr2;
                    instr2.address = current_addr;
                    instr2.binary_code = static_cast<uint32_t>(second_half);
                    instr2.index = text_section.instructions.size();
                    text_section.instructions.push_back(instr2);
                    current_addr += 2;
                } else {
                    // Second half starts a 32-bit instruction, need to re-read
                    // This case is complex, for simplicity we'll just skip
                }
            }
        }
        
        instruction_count++;
    }

    text_section_ = std::move(text_section);
    return true;
}

} // namespace elf_parser
