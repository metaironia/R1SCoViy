#ifndef SRC_SIMULATOR_SPU_ISA_INSTRUCTIONTYPES_H
#define SRC_SIMULATOR_SPU_ISA_INSTRUCTIONTYPES_H

#include <cstdint>

namespace r1scoviy {

class ExecutorUnit;

const int FUNCT3_STARTBIT = 12;
const int FUNCT7_STARTBIT = 25;
const int BITWISE_FIXED_IMM = 25;

struct InstrParams {
    uint32_t Imm;
    uint32_t Rs1;
    uint32_t Rs2;
    uint32_t Rd;
};

class Instruction {
protected:
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
    RTypeInstruction(uint32_t _Opcode, uint32_t _Funct3, uint32_t _Funct7) 
        : Instruction(_Opcode), Funct3(_Funct3), Funct7(_Funct7) {}

    uint32_t getInstrID() const override { return (Funct7 << FUNCT7_STARTBIT) | (Funct3 << FUNCT3_STARTBIT) | Opcode; }
};

class ITypeInstruction : public Instruction {
protected:
    uint32_t Funct3;

public:
    ITypeInstruction(uint32_t _Opcode, uint32_t _Funct3) 
        : Instruction(_Opcode), Funct3(_Funct3) {}

    uint32_t getInstrID() const override { return (Funct3 << FUNCT3_STARTBIT) | Opcode; }
};

class BitwiseITypeInstruction : public ITypeInstruction {
private:
    uint32_t Imm5_11;

public:
    BitwiseITypeInstruction(uint32_t _Opcode, uint32_t _Funct3, uint32_t _Imm5_11) 
        : ITypeInstruction(_Opcode, _Funct3), Imm5_11(_Imm5_11) {}

    uint32_t getInstrID() const override { return (Imm5_11 << BITWISE_FIXED_IMM) | (Funct3 << FUNCT3_STARTBIT) | Opcode; }
};

class STypeInstruction : public Instruction {
private:
    uint32_t Funct3;

public:
    STypeInstruction(uint32_t _Opcode, uint32_t _Funct3) 
        : Instruction(_Opcode), Funct3(_Funct3) {}

    uint32_t getInstrID() const override { return (Funct3 << FUNCT3_STARTBIT) | Opcode; }
};

class BTypeInstruction : public Instruction {
private:
    uint32_t Funct3;

public:
    BTypeInstruction(uint32_t _Opcode, uint32_t _Funct3) 
        : Instruction(_Opcode), Funct3(_Funct3) {}

    uint32_t getInstrID() const override { return (Funct3 << FUNCT3_STARTBIT) | Opcode; }
};

class UTypeInstruction : public Instruction {
public:
    UTypeInstruction(uint32_t _Opcode) 
        : Instruction(_Opcode) {}

    uint32_t getInstrID() const override { return Opcode; }
};

class JTypeInstruction : public Instruction {
public:
    JTypeInstruction(uint32_t _Opcode) 
        : Instruction(_Opcode) {}

    uint32_t getInstrID() const override { return Opcode; }
};

} // namespace r1scoviy

#endif