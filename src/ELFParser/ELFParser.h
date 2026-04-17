#ifndef ELF_PARSER_H
#define ELF_PARSER_H

#include <cstdint>
#include <string>
#include <vector>
#include <optional>
#include <memory>

// Forward declaration - elfio is heavy, we'll use pimpl pattern
namespace ELFIO {
    class elfio;
}

namespace elf_parser {

/**
 * @brief Represents a single RISC-V instruction parsed from the .text section
 */
struct Instruction {
    uint64_t address;      // Virtual address of the instruction
    uint32_t binary_code;  // Raw 32-bit instruction binary
    size_t index;          // Index in the instructions vector
};

/**
 * @brief Parsed .text section data containing all instructions
 */
struct TextSection {
    std::string name;           // Section name (should be ".text")
    uint64_t base_address;      // Starting virtual address of the section
    std::vector<Instruction> instructions;  // All parsed instructions
    
    /**
     * @brief Find instruction index by address
     * @param address Virtual address to search for
     * @return Optional index if found, nullopt otherwise
     */
    [[nodiscard]] std::optional<size_t> findInstructionIndexByAddress(uint64_t address) const;
};

/**
 * @brief ELF file parser for RISC-V 64-bit ELF files
 * 
 * Uses PIMPL pattern to hide elfio dependency in header
 */
class ELFParser {
public:
    ELFParser();
    ~ELFParser();
    
    // Non-copyable, non-movable for RAII safety with elfio resources
    ELFParser(const ELFParser&) = delete;
    ELFParser& operator=(const ELFParser&) = delete;
    ELFParser(ELFParser&&) = delete;
    ELFParser& operator=(ELFParser&&) = delete;

    /**
     * @brief Load and parse an ELF file
     * @param filepath Path to the ELF file
     * @return true if successfully loaded and parsed, false otherwise
     */
    bool loadFile(const std::string& filepath);

    /**
     * @brief Check if a file is currently loaded
     * @return true if a file is loaded, false otherwise
     */
    [[nodiscard]] bool isLoaded() const { return text_section_.has_value(); }

    /**
     * @brief Get the parsed .text section
     * @return Pointer to text section if loaded, nullptr otherwise
     */
    [[nodiscard]] const TextSection* getTextSection() const {
        return text_section_.has_value() ? &text_section_.value() : nullptr;
    }

    /**
     * @brief Get the entry point address of the ELF file
     * @return Entry point address, or 0 if not loaded
     */
    [[nodiscard]] uint64_t getEntryPoint() const { return entry_point_; }

    /**
     * @brief Get the last error message
     * @return Error message string
     */
    [[nodiscard]] const std::string& getLastError() const { return last_error_; }

private:
    std::unique_ptr<ELFIO::elfio> elf_reader_;  // PIMPL for elfio
    std::optional<TextSection> text_section_;
    uint64_t entry_point_ = 0;
    std::string last_error_;

    /**
     * @brief Parse the .text section from ELF data
     * @return true if successfully parsed, false otherwise
     */
    bool parseTextSection();
};

} // namespace elf_parser

#endif // ELF_PARSER_H
