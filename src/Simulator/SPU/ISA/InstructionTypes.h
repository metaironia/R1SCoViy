#ifndef SRC_SIMULATOR_SPU_ISA_INSTRUCTIONTYPES_H
#define SRC_SIMULATOR_SPU_ISA_INSTRUCTIONTYPES_H

#include <cstdint>
#include <memory>

#include "MathHelper/MathHelper.h"
#include "Simulator/SPU/Executor/InstructionDispatcher.h"
#include "InstructionParams.h"

namespace r1scoviy {

class ExecutorUnit;

class Instruction {
protected:
    uint32_t Opcode;

public:
    Instruction(uint32_t _Opcode) 
        : Opcode(_Opcode) {}

    virtual void executeInstr(ExecutorUnit &TargetExecutor) const = 0;

    virtual uint32_t getInstrID() const = 0;

    virtual std::shared_ptr<InstructionDispatcher> getDispatcher() = 0;

    virtual uint32_t getOpcode() const { return Opcode; }

    virtual ~Instruction() = default;
};

class RTypeInstruction : public Instruction {
private:
    uint32_t Funct3;
    uint32_t Funct7;

public:
    RTypeInstruction(uint32_t _Opcode, uint32_t _Funct3, uint32_t _Funct7) 
        : Instruction(_Opcode), Funct3(_Funct3), Funct7(_Funct7) {}

    virtual std::shared_ptr<InstructionDispatcher> getDispatcher() override { return std::make_shared<RTypeInstructionDispatcher>(); }

    uint32_t getInstrID() const override { return (Funct7 << FUNCT7_STARTBIT) | (Funct3 << FUNCT3_STARTBIT) | Opcode; }
};

class ITypeInstruction : public Instruction {
protected:
    uint32_t Funct3;

public:
    ITypeInstruction(uint32_t _Opcode, uint32_t _Funct3) 
        : Instruction(_Opcode), Funct3(_Funct3) {}

    virtual std::shared_ptr<InstructionDispatcher> getDispatcher() override { return std::make_shared<ITypeInstructionDispatcher>(); }
    uint32_t getInstrID() const override { return (Funct3 << FUNCT3_STARTBIT) | Opcode; }

    int32_t getSignExtImm(uint32_t Imm) const { return GetSignExtImm(Imm, 11); }
};

class BitwiseITypeInstruction : public ITypeInstruction {
private:
    uint32_t Imm5_11;

public:
    BitwiseITypeInstruction(uint32_t _Opcode, uint32_t _Funct3, uint32_t _Imm5_11) 
        : ITypeInstruction(_Opcode, _Funct3), Imm5_11(_Imm5_11) {}

    virtual std::shared_ptr<InstructionDispatcher> getDispatcher() override { return std::make_shared<BitwiseITypeInstructionDispatcher>(); }
    uint32_t getInstrID() const override { return (Imm5_11 << BITWISE_FIXED_IMM) | (Funct3 << FUNCT3_STARTBIT) | Opcode; }

    int32_t getSignExtImm(uint32_t Imm) const { return GetSignExtImm(Imm, 4); }
};

class STypeInstruction : public Instruction {
private:
    uint32_t Funct3;

public:
    STypeInstruction(uint32_t _Opcode, uint32_t _Funct3) 
        : Instruction(_Opcode), Funct3(_Funct3) {}

    virtual std::shared_ptr<InstructionDispatcher> getDispatcher() override { return std::make_shared<STypeInstructionDispatcher>(); }
    uint32_t getInstrID() const override { return (Funct3 << FUNCT3_STARTBIT) | Opcode; }

    int32_t getSignExtImm(uint32_t Imm) const { return GetSignExtImm(Imm, 11); }
};

class BTypeInstruction : public Instruction {
private:
    uint32_t Funct3;

public:
    BTypeInstruction(uint32_t _Opcode, uint32_t _Funct3) 
        : Instruction(_Opcode), Funct3(_Funct3) {}

    virtual std::shared_ptr<InstructionDispatcher> getDispatcher() override { return std::make_shared<BTypeInstructionDispatcher>(); }
    uint32_t getInstrID() const override { return (Funct3 << FUNCT3_STARTBIT) | Opcode; }

    int32_t getSignExtImm(uint32_t Imm) const { return GetSignExtImm(Imm, 12); }
};

class UTypeInstruction : public Instruction {
public:
    UTypeInstruction(uint32_t _Opcode) 
        : Instruction(_Opcode) {}

    virtual std::shared_ptr<InstructionDispatcher> getDispatcher() override { return std::make_shared<UTypeInstructionDispatcher>(); }
    uint32_t getInstrID() const override { return Opcode; }
};

class JTypeInstruction : public Instruction {
public:
    JTypeInstruction(uint32_t _Opcode) 
        : Instruction(_Opcode) {}

    virtual std::shared_ptr<InstructionDispatcher> getDispatcher() override { return std::make_shared<JTypeInstructionDispatcher>(); }
    uint32_t getInstrID() const override { return Opcode; }

    int32_t getSignExtImm(uint32_t Imm) const { return GetSignExtImm(Imm, 20); }
};

class R4TypeInstruction : public Instruction {
public:
    R4TypeInstruction(uint32_t _Opcode) 
        : Instruction(_Opcode) {}

    virtual std::shared_ptr<InstructionDispatcher> getDispatcher() override { return std::make_shared<R4TypeInstructionDispatcher>(); }
    uint32_t getInstrID() const override { return Opcode; }
};

class FloatTypeRoundingInstruction : public Instruction {
private:
    uint32_t Funct5;

public:
    FloatTypeRoundingInstruction(uint32_t _Opcode, uint32_t _Funct5) 
        : Instruction(_Opcode), Funct5(_Funct5) {}

    virtual std::shared_ptr<InstructionDispatcher> getDispatcher() override { return std::make_shared<FloatTypeRoundingInstructionDispatcher>(); }
    uint32_t getInstrID() const override { return getOpcode(); }

    virtual uint32_t getOpcode() const override { return (Funct5 << FUNCT5_STARTBIT) | Opcode; }
};

class FloatTypeNoRoundingInstruction : public Instruction {
private:
    uint32_t Funct3;
    uint32_t Funct5;

public:
    FloatTypeNoRoundingInstruction(uint32_t _Opcode, uint32_t _Funct3, uint32_t _Funct5) 
        : Instruction(_Opcode), Funct3(_Funct3), Funct5(_Funct5) {}

    virtual std::shared_ptr<InstructionDispatcher> getDispatcher() override { return std::make_shared<FloatTypeNoRoundingInstructionDispatcher>(); }
    uint32_t getInstrID() const override { return (Funct3 << FUNCT3_STARTBIT) | getOpcode(); }

    virtual uint32_t getOpcode() const override { return (Funct5 << FUNCT5_STARTBIT) | Opcode; }
};

} // namespace r1scoviy

#endif