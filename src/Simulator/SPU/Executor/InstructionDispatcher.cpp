#include "Simulator/SPU/ISA/InstructionTypes.h"
#include "InstructionDispatcher.h"

namespace r1scoviy {

uint32_t RTypeInstructionDispatcher::getInstrID(uint32_t Instr) const {
    
    const uint32_t Opcode = getOpcode(Instr);
    const uint32_t Funct3 = getFunct3(Instr);
    const uint32_t Funct7 = getFunct7(Instr);

    return (Funct7 << FUNCT7_STARTBIT) | (Funct3 << FUNCT3_STARTBIT) | Opcode;
}

void RTypeInstructionDispatcher::setInstrParams(uint32_t Instr, InstrParams &CurrInstrParams) const {

    CurrInstrParams.Rd = getRdNum(Instr);
    CurrInstrParams.Rs1 = getRs1Num(Instr);
    CurrInstrParams.Rs2 = getRs2Num(Instr);
}

uint32_t ITypeInstructionDispatcher::getInstrID(uint32_t Instr) const {
   
    const uint32_t Opcode = getOpcode(Instr);
    const uint32_t Funct3 = getFunct3(Instr);

    return (Funct3 << FUNCT3_STARTBIT) | Opcode;
}

void ITypeInstructionDispatcher::setInstrParams(uint32_t Instr, InstrParams &CurrInstrParams) const {

    CurrInstrParams.Rd = getRdNum(Instr);
    CurrInstrParams.Rs1 = getRs1Num(Instr);
    CurrInstrParams.Imm = getImm(Instr);
}

uint32_t BitwiseITypeInstructionDispatcher::getInstrID(uint32_t Instr) const {
   
    const uint32_t Opcode = getOpcode(Instr);
    const uint32_t Funct3 = getFunct3(Instr);
    const uint32_t FixedImm = getFixedImm(Instr);

    return (FixedImm << BITWISE_FIXED_IMM) | (Funct3 << FUNCT3_STARTBIT) | Opcode;
}

void BitwiseITypeInstructionDispatcher::setInstrParams(uint32_t Instr, InstrParams &CurrInstrParams) const {

    CurrInstrParams.Rd = getRdNum(Instr);
    CurrInstrParams.Rs1 = getRs1Num(Instr);
    CurrInstrParams.Imm = getImm(Instr);
}

uint32_t STypeInstructionDispatcher::getInstrID(uint32_t Instr) const {
    
    const uint32_t Opcode = getOpcode(Instr);
    const uint32_t Funct3 = getFunct3(Instr);

    return (Funct3 << FUNCT3_STARTBIT) | Opcode;
}

void STypeInstructionDispatcher::setInstrParams(uint32_t Instr, InstrParams &CurrInstrParams) const {

    CurrInstrParams.Rs1 = getRs1Num(Instr);
    CurrInstrParams.Rs2 = getRs2Num(Instr);
    CurrInstrParams.Imm = getMergedImm(Instr);
}

uint32_t BTypeInstructionDispatcher::getInstrID(uint32_t Instr) const {
    
    const uint32_t Opcode = getOpcode(Instr);
    const uint32_t Funct3 = getFunct3(Instr);

    return (Funct3 << FUNCT3_STARTBIT) | Opcode;
}

void BTypeInstructionDispatcher::setInstrParams(uint32_t Instr, InstrParams &CurrInstrParams) const {

    CurrInstrParams.Rs1 = getRs1Num(Instr);
    CurrInstrParams.Rs2 = getRs2Num(Instr);
    CurrInstrParams.Imm = getMergedImm(Instr);
}

uint32_t UTypeInstructionDispatcher::getInstrID(uint32_t Instr) const {
    
    const uint32_t Opcode = getOpcode(Instr);

    return Opcode;
}

void UTypeInstructionDispatcher::setInstrParams(uint32_t Instr, InstrParams &CurrInstrParams) const {

    CurrInstrParams.Rd = getRdNum(Instr);
    CurrInstrParams.Imm = getImm(Instr);
}

uint32_t JTypeInstructionDispatcher::getInstrID(uint32_t Instr) const {
    
    const uint32_t Opcode = getOpcode(Instr);

    return Opcode;
}

void JTypeInstructionDispatcher::setInstrParams(uint32_t Instr, InstrParams &CurrInstrParams) const {

    CurrInstrParams.Rd = getRdNum(Instr);
    CurrInstrParams.Imm = getMergedImm(Instr);
}

uint32_t JTypeInstructionDispatcher::getMergedImm(uint32_t Instr) const {

    const uint32_t Bit20 = ExtractBits(Instr, 31, 31);      // imm[20] - sign bit
    const uint32_t Bits10to1 = ExtractBits(Instr, 21, 30);  // imm[10:1]
    const uint32_t Bit11 = ExtractBits(Instr, 20, 20);      // imm[11]
    const uint32_t Bits19to12 = ExtractBits(Instr, 12, 19); // imm[19:12]

    return (Bit20 << 20) | (Bits10to1 << 1) | (Bit11 << 11) | (Bits19to12 << 12);
}

uint32_t STypeInstructionDispatcher::getMergedImm(uint32_t Instr) const {
    const uint32_t Imm11to5 = ExtractBits(Instr, 25, 31);   // imm[11:5]
    const uint32_t Imm4to0 = ExtractBits(Instr, 7, 11);     // imm[4:0]

    return (Imm11to5 << 5) | Imm4to0;
}

uint32_t BTypeInstructionDispatcher::getMergedImm(uint32_t Instr) const {
    const uint32_t Bit12 = ExtractBits(Instr, 31, 31);      // imm[12] - sign bit
    const uint32_t Bits10to5 = ExtractBits(Instr, 25, 30);  // imm[10:5]
    const uint32_t Bits4to1 = ExtractBits(Instr, 8, 11);    // imm[4:1]
    const uint32_t Bit11 = ExtractBits(Instr, 7, 7);        // imm[11]

    return (Bit12 << 12) | (Bits10to5 << 5) | (Bits4to1 << 1) | (Bit11 << 11);
}

} // namespace r1scoviy