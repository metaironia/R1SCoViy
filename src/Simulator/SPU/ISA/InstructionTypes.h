#ifndef SRC_SIMULATOR_SPU_ISA_INSTRUCTIONTYPES_H
#define SRC_SIMULATOR_SPU_ISA_INSTRUCTIONTYPES_H

#include <cstdint>

namespace r1scoviy {

class ExecutorUnit;

class Instruction {
private:
    uint32_t Opcode;

public:
    Instruction(uint32_t _Opcode) 
        : Opcode(_Opcode) {}

    virtual void executeInstr(ExecutorUnit &TargetExecutor) const = 0;

    virtual uint32_t getInstrID() const = 0;

    uint32_t getOpcode() const { return Opcode; }

    virtual ~Instruction() = default;
};

class RTypeInstruction : public Instruction {
private:
    uint32_t Funct3;
    uint32_t Funct7;

public:
    RTypeInstruction(uint32_t Opcode, uint32_t _Funct3, uint32_t _Funct7) 
        : Instruction(Opcode), Funct3(_Funct3), Funct7(_Funct7) {}

    uint32_t getInstrID() const override { return (Funct7 << 10) | (Funct3 << 7) | getOpcode(); }
};

class ITypeInstruction : public Instruction {
private:
    uint32_t Funct3;

public:
    ITypeInstruction(uint32_t Opcode, uint32_t _Funct3) 
        : Instruction(Opcode), Funct3(_Funct3) {}

    uint32_t getInstrID() const override { return (Funct3 << 7) | getOpcode(); }
};

class STypeInstruction : public Instruction {
private:
    uint32_t Funct3;

public:
    STypeInstruction(uint32_t Opcode, uint32_t _Funct3) 
        : Instruction(Opcode), Funct3(_Funct3) {}

    uint32_t getInstrID() const override { return (Funct3 << 7) | getOpcode(); }
};

class BTypeInstruction : public Instruction {
private:
    uint32_t Funct3;

public:
    BTypeInstruction(uint32_t Opcode, uint32_t _Funct3) 
        : Instruction(Opcode), Funct3(_Funct3) {}

    uint32_t getInstrID() const override { return (Funct3 << 7) | getOpcode(); }
};

class UTypeInstruction : public Instruction {
public:
    UTypeInstruction(uint32_t Opcode) 
        : Instruction(Opcode) {}

    uint32_t getInstrID() const override { return getOpcode(); }
};

class JTypeInstruction : public Instruction {
public:
    JTypeInstruction(uint32_t Opcode) 
        : Instruction(Opcode) {}

    uint32_t getInstrID() const override { return getOpcode(); }
};

} // namespace r1scoviy

#endif