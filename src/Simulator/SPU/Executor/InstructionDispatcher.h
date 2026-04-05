#ifndef SRC_SIMULATOR_SPU_EXECUTOR_INSTRUCTIONDISPATCHER_H
#define SRC_SIMULATOR_SPU_EXECUTOR_INSTRUCTIONDISPATCHER_H

#include <cstdint>

namespace r1scoviy {

class InstructionDispatcher {
public:
    virtual uint32_t getInstrID(uint32_t Instr) const = 0;

protected:
    virtual ~InstructionDispatcher() = default;

public:
    static uint32_t extractBits(uint32_t Instruction, int StartBit, int EndBit);

    static uint32_t getOpcode(uint32_t Instr) { return extractBits(Instr, 0, 6); }
};

class RTypeInstructionDispatcher: public InstructionDispatcher {
public:
    uint32_t getInstrID(uint32_t Instr) const override;

    uint32_t getRdNum(uint32_t Instr) const { return extractBits(Instr, 7, 11); }
    uint32_t getFunct3(uint32_t Instr) const { return extractBits(Instr, 12, 14); }
    uint32_t getRs1Num(uint32_t Instr) const { return extractBits(Instr, 15, 19); }
    uint32_t getRs2Num(uint32_t Instr) const { return extractBits(Instr, 20, 24); }
    uint32_t getFunct7(uint32_t Instr) const { return extractBits(Instr, 25, 31); }
};

class ITypeInstructionDispatcher: public InstructionDispatcher {
public:
    uint32_t getInstrID(uint32_t Instr) const override;

    uint32_t getRdNum(uint32_t Instr) const { return extractBits(Instr, 7, 11); }
    uint32_t getFunct3(uint32_t Instr) const { return extractBits(Instr, 12, 14); }
    uint32_t getRs1Num(uint32_t Instr) const { return extractBits(Instr, 15, 19); }
    uint32_t getImm(uint32_t Instr) const { return extractBits(Instr, 20, 31); }
};

class STypeInstructionDispatcher : public InstructionDispatcher {
public:
    uint32_t getInstrID(uint32_t Instr) const override;

    uint32_t getFunct3(uint32_t Instr) const { return extractBits(Instr, 12, 14); }
    uint32_t getRs2Num(uint32_t Instr) const { return extractBits(Instr, 20, 24); }
    uint32_t getRs1Num(uint32_t Instr) const { return extractBits(Instr, 15, 19); }

    uint32_t getMergedImm(uint32_t Instr) const;
};

class BTypeInstructionDispatcher : public InstructionDispatcher {
public:
    uint32_t getInstrID(uint32_t Instr) const override;

    uint32_t getFunct3(uint32_t Instr) const { return extractBits(Instr, 12, 14); }
    uint32_t getRs2Num(uint32_t Instr) const { return extractBits(Instr, 20, 24); }
    uint32_t getRs1Num(uint32_t Instr) const { return extractBits(Instr, 15, 19); }

    uint32_t getMergedImm(uint32_t Instr) const;
};

class UTypeInstructionDispatcher : public InstructionDispatcher {
public:
    uint32_t getInstrID(uint32_t Instr) const override;

    uint32_t getImm(uint32_t Instr) const { return extractBits(Instr, 12, 31); }
    uint32_t getRdNum(uint32_t Instr) const { return extractBits(Instr, 7, 11); }
};

class JTypeInstructionDispatcher : public InstructionDispatcher {
public:
    uint32_t getMergedImm(uint32_t Instr) const;
    uint32_t getRdNum(uint32_t Instr) const { return extractBits(Instr, 7, 11); }
};

class R4TypeInstructionDispatcher : public InstructionDispatcher {
public:
    uint32_t getFs3Num(uint32_t Instr) const { return extractBits(Instr, 27, 31); }
    uint32_t getFs2Num(uint32_t Instr) const { return extractBits(Instr, 20, 24); }
    uint32_t getFs1Num(uint32_t Instr) const { return extractBits(Instr, 15, 19); }
    uint32_t getFdNum(uint32_t Instr) const { return extractBits(Instr, 7, 11); }
};

} // namespace r1scoviy

#endif