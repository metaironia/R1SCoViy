#ifndef FETCHER_H
#define FETCHER_H

#include <cstdint>
#include <optional>
#include <memory>
#include <string>

// Forward declaration
namespace elf_parser {
    class ELFParser;
    struct TextSection;
}

namespace fetcher {

/**
 * @brief Exception class for fetcher errors
 */
class FetcherException : public std::exception {
public:
    explicit FetcherException(const char* message) : msg_(message) {}
    explicit FetcherException(const std::string& message) : msg_(message) {}
    
    [[nodiscard]] const char* what() const noexcept override {
        return msg_.c_str();
    }

private:
    std::string msg_;
};

/**
 * @brief Instruction fetcher that retrieves binary instructions from parsed ELF data
 * 
 * This class provides an interface to fetch RISC-V instructions by program counter (PC).
 * It maintains the current PC state and allows sequential or random-access instruction fetching.
 */
class Fetcher {
public:
    /**
     * @brief Construct a new Fetcher with an ELF parser
     * @param parser Pointer to a loaded ELFParser instance (must outlive Fetcher)
     */
    explicit Fetcher(const elf_parser::ELFParser* parser);
    
    ~Fetcher() = default;
    
    // Non-copyable
    Fetcher(const Fetcher&) = delete;
    Fetcher& operator=(const Fetcher&) = delete;
    
    // Movable
    Fetcher(Fetcher&&) noexcept = default;
    Fetcher& operator=(Fetcher&&) noexcept = default;

    /**
     * @brief Fetch the instruction at the current PC
     * @return 32-bit instruction binary code
     * @throws FetcherException if no instruction exists at current PC
     */
    [[nodiscard]] uint32_t fetchInstruction();

    /**
     * @brief Fetch the instruction at a specific address without changing current PC
     * @param address Virtual address to fetch from
     * @return Optional instruction binary code, nullopt if address not found
     */
    [[nodiscard]] std::optional<uint32_t> peekInstruction(uint64_t address) const;

    /**
     * @brief Set the current program counter
     * @param pc New PC value
     * @return true if PC points to a valid instruction, false otherwise
     */
    bool setPC(uint64_t pc);

    /**
     * @brief Get the current program counter
     * @return Current PC value
     */
    [[nodiscard]] uint64_t getPC() const { return current_pc_; }

    /**
     * @brief Advance the PC by the size of the current instruction
     * @return true if successfully advanced, false if at end of section
     */
    bool step();

    /**
     * @brief Check if the current PC is within valid instruction range
     * @return true if PC points to a valid instruction
     */
    [[nodiscard]] bool isValidPC() const;

    /**
     * @brief Reset the PC to the ELF entry point
     * @return true if entry point is valid
     */
    bool reset();

    /**
     * @brief Get the base address of the .text section
     * @return Base address, or 0 if not loaded
     */
    [[nodiscard]] uint64_t getTextSectionBase() const;

    /**
     * @brief Get the size of the .text section in instructions
     * @return Number of instructions, or 0 if not loaded
     */
    [[nodiscard]] size_t getInstructionCount() const;

private:
    const elf_parser::ELFParser* parser_;  // Non-owning pointer
    uint64_t current_pc_ = 0;
    
    /**
     * @brief Find the instruction index for a given address
     * @param address Address to search for
     * @return Optional index if found
     */
    [[nodiscard]] std::optional<size_t> findInstructionIndex(uint64_t address) const;
    
    /**
     * @brief Get the text section from parser
     * @return Pointer to text section, nullptr if not available
     */
    [[nodiscard]] const elf_parser::TextSection* getTextSection() const;
};

} // namespace fetcher

#endif // FETCHER_H
