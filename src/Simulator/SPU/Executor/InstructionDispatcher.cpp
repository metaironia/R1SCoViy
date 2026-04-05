#include "InstructionDispatcher.h"

namespace r1scoviy {

uint32_t InstructionDispatcher::extractBits(uint32_t Instruction, int StartBit, int EndBit) {
   
    if (StartBit > EndBit || EndBit > 31)
        return 0;

    const int Width = EndBit - StartBit + 1;

    const uint32_t Mask = (Width == 32) ? 0xFFFFFFFFU : ((1U << Width) - 1);

    return (Instruction >> StartBit) & Mask;
}

uint32_t RTypeInstructionDispatcher::getInstrID(uint32_t Instr) const {
    
    const uint32_t Opcode = getOpcode(Instr);
    const uint32_t Funct3 = getFunct3(Instr);
    const uint32_t Funct7 = getFunct7(Instr);

    return (Funct7 << 10) | (Funct3 << 7) | Opcode;
}

uint32_t ITypeInstructionDispatcher::getInstrID(uint32_t Instr) const {
   
    const uint32_t Opcode = getOpcode(Instr);
    const uint32_t Funct3 = getFunct3(Instr);

    return (Funct3 << 7) | Opcode;
}

uint32_t STypeInstructionDispatcher::getInstrID(uint32_t Instr) const {
    
    const uint32_t Opcode = getOpcode(Instr);
    const uint32_t Funct3 = getFunct3(Instr);

    return (Funct3 << 7) | Opcode;
}

uint32_t BTypeInstructionDispatcher::getInstrID(uint32_t Instr) const {
    
    const uint32_t Opcode = getOpcode(Instr);
    const uint32_t Funct3 = getFunct3(Instr);

    return (Funct3 << 7) | Opcode;
}

uint32_t UTypeInstructionDispatcher::getInstrID(uint32_t Instr) const {
    
    const uint32_t Opcode = getOpcode(Instr);

    return Opcode;
}

uint32_t JTypeInstructionDispatcher::getMergedImm(uint32_t Instr) const {

    const uint32_t Bit20 = extractBits(Instr, 31, 31);      // imm[20] - sign bit
    const uint32_t Bits10to1 = extractBits(Instr, 21, 30);  // imm[10:1]
    const uint32_t Bit11 = extractBits(Instr, 20, 20);      // imm[11]
    const uint32_t Bits19to12 = extractBits(Instr, 12, 19); // imm[19:12]

    uint32_t Imm = (Bit20 << 20) | (Bits10to1 << 1) | (Bit11 << 11) | (Bits19to12 << 12);

    if (Bit20) {
        Imm |= 0xFFFFF000U;
    }

    return Imm;
}

uint32_t STypeInstructionDispatcher::getMergedImm(uint32_t Instr) const {
    const uint32_t Imm11to5 = extractBits(Instr, 25, 31);   // imm[11:5]
    const uint32_t Imm4to0 = extractBits(Instr, 7, 11);     // imm[4:0]

    return (Imm11to5 << 5) | Imm4to0;
}

uint32_t BTypeInstructionDispatcher::getMergedImm(uint32_t Instr) const {
    const uint32_t Bit12 = extractBits(Instr, 31, 31);      // imm[12] - sign bit
    const uint32_t Bits10to5 = extractBits(Instr, 25, 30);  // imm[10:5]
    const uint32_t Bits4to1 = extractBits(Instr, 8, 11);    // imm[4:1]
    const uint32_t Bit11 = extractBits(Instr, 7, 7);        // imm[11]

    return (Bit12 << 12) | (Bits10to5 << 5) | (Bits4to1 << 1) | (Bit11 << 11);
}

} // namespace r1scoviy