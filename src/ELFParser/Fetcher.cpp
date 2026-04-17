#include "Fetcher.h"
#include "ELFParser.h"

#include <stdexcept>

namespace fetcher {

Fetcher::Fetcher(const elf_parser::ELFParser* parser)
    : parser_(parser) {
    if (parser_ == nullptr) {
        throw FetcherException("ELFParser pointer cannot be null");
    }
}

uint32_t Fetcher::fetchInstruction() {
    const auto* text_section = getTextSection();
    if (text_section == nullptr) {
        throw FetcherException("No ELF file loaded");
    }

    auto index_opt = findInstructionIndex(current_pc_);
    if (!index_opt.has_value()) {
        throw FetcherException("No instruction at current PC: " + 
                               std::to_string(current_pc_));
    }

    const auto& instr = text_section->instructions[*index_opt];
    return instr.binary_code;
}

std::optional<uint32_t> Fetcher::peekInstruction(uint64_t address) const {
    const auto* text_section = getTextSection();
    if (text_section == nullptr) {
        return std::nullopt;
    }

    auto index_opt = findInstructionIndex(address);
    if (!index_opt.has_value()) {
        return std::nullopt;
    }

    return text_section->instructions[*index_opt].binary_code;
}

bool Fetcher::setPC(uint64_t pc) {
    const auto* text_section = getTextSection();
    if (text_section == nullptr) {
        return false;
    }

    auto index_opt = findInstructionIndex(pc);
    if (index_opt.has_value()) {
        current_pc_ = pc;
        return true;
    }
    return false;
}

bool Fetcher::step() {
    const auto* text_section = getTextSection();
    if (text_section == nullptr) {
        return false;
    }

    auto index_opt = findInstructionIndex(current_pc_);
    if (!index_opt.has_value()) {
        return false;
    }

    const auto& current_instr = text_section->instructions[*index_opt];
    
    // Determine instruction size from the binary code
    // RISC-V compressed instructions have opcode bits [1:0] != 11
    uint8_t opcode_low2 = current_instr.binary_code & 0x3;
    size_t instr_size = (opcode_low2 == 0x3) ? 4 : 2;
    
    uint64_t next_pc = current_pc_ + instr_size;
    
    // Check if next PC is valid
    auto next_index_opt = findInstructionIndex(next_pc);
    if (next_index_opt.has_value()) {
        current_pc_ = next_pc;
        return true;
    }
    
    // Check if we've reached the end
    if (*index_opt + 1 >= text_section->instructions.size()) {
        return false;  // End of section
    }
    
    // Try to advance to the next instruction in the vector
    const auto& next_instr = text_section->instructions[*index_opt + 1];
    current_pc_ = next_instr.address;
    return true;
}

bool Fetcher::isValidPC() const {
    return findInstructionIndex(current_pc_).has_value();
}

bool Fetcher::reset() {
    if (!parser_->isLoaded()) {
        return false;
    }

    uint64_t entry_point = parser_->getEntryPoint();
    if (entry_point == 0) {
        return false;
    }

    return setPC(entry_point);
}

uint64_t Fetcher::getTextSectionBase() const {
    const auto* text_section = getTextSection();
    if (text_section == nullptr) {
        return 0;
    }
    return text_section->base_address;
}

size_t Fetcher::getInstructionCount() const {
    const auto* text_section = getTextSection();
    if (text_section == nullptr) {
        return 0;
    }
    return text_section->instructions.size();
}

std::optional<size_t> Fetcher::findInstructionIndex(uint64_t address) const {
    const auto* text_section = getTextSection();
    if (text_section == nullptr) {
        return std::nullopt;
    }
    return text_section->findInstructionIndexByAddress(address);
}

const elf_parser::TextSection* Fetcher::getTextSection() const {
    if (parser_ == nullptr || !parser_->isLoaded()) {
        return nullptr;
    }
    return parser_->getTextSection();
}

} // namespace fetcher
