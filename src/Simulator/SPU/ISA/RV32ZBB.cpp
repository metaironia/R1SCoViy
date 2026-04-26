#include "RV32ZBB.h"
#include "MathHelper/MathHelper.h"
#include "Simulator/SPU/Executor/Executor.h"
#include <memory>

namespace r1scoviy {

ANDNInstruction::ANDNInstruction() : RTypeInstruction(0x33, 0x7, 0x20) {}

void ANDNInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1);
    int32_t Rs2Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs2);
    int32_t Result = Rs1Val & ~Rs2Val;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

ORNInstruction::ORNInstruction() : RTypeInstruction(0x33, 0x6, 0x20) {}

void ORNInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1);
    int32_t Rs2Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs2);
    int32_t Result = Rs1Val | ~Rs2Val;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

XNORInstruction::XNORInstruction() : RTypeInstruction(0x33, 0x4, 0x21) {}

void XNORInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1);
    int32_t Rs2Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs2);
    int32_t Result = ~(Rs1Val ^ Rs2Val);
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

MAXInstruction::MAXInstruction() : RTypeInstruction(0x33, 0x6, 0x5) {}

void MAXInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1);
    int32_t Rs2Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs2);
    int32_t Result = (Rs1Val > Rs2Val) ? Rs1Val : Rs2Val;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

MAXUInstruction::MAXUInstruction() : RTypeInstruction(0x33, 0x7, 0x5) {}

void MAXUInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = static_cast<uint32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1));
    uint32_t Rs2Val = static_cast<uint32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs2));
    uint32_t Result = (Rs1Val > Rs2Val) ? Rs1Val : Rs2Val;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, static_cast<int32_t>(Result));
    TargetExecutor.getPC() += 4;
}

MINInstruction::MINInstruction() : RTypeInstruction(0x33, 0x4, 0x5) {}

void MINInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1);
    int32_t Rs2Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs2);
    int32_t Result = (Rs1Val < Rs2Val) ? Rs1Val : Rs2Val;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

MINUInstruction::MINUInstruction() : RTypeInstruction(0x33, 0x5, 0x5) {}

void MINUInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = static_cast<uint32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1));
    uint32_t Rs2Val = static_cast<uint32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs2));
    uint32_t Result = (Rs1Val < Rs2Val) ? Rs1Val : Rs2Val;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, static_cast<int32_t>(Result));
    TargetExecutor.getPC() += 4;
}

ROLInstruction::ROLInstruction() : RTypeInstruction(0x33, 0x1, 0x30) {}

void ROLInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = static_cast<uint32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1));
    int32_t Rs2Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs2);
    uint32_t Shamt = Rs2Val & 0x1F;
    uint32_t Result = (Rs1Val << Shamt) | (Rs1Val >> (32 - Shamt));
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, static_cast<int32_t>(Result));
    TargetExecutor.getPC() += 4;
}

RORInstruction::RORInstruction() : RTypeInstruction(0x33, 0x5, 0x30) {}

void RORInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = static_cast<uint32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1));
    int32_t Rs2Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs2);
    uint32_t Shamt = Rs2Val & 0x1F;
    uint32_t Result = (Rs1Val >> Shamt) | (Rs1Val << (32 - Shamt));
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, static_cast<int32_t>(Result));
    TargetExecutor.getPC() += 4;
}

SEXTBInstruction::SEXTBInstruction() : UltraBitwiseITypeInstruction(static_cast<uint32_t>(Opcodes::OP_IMM), 0x1, 0x604) {}

void SEXTBInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1);
    int8_t ByteVal = static_cast<int8_t>(Rs1Val & 0xFF);
    int32_t Result = static_cast<int32_t>(ByteVal);
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

SEXTHInstruction::SEXTHInstruction() : UltraBitwiseITypeInstruction(static_cast<uint32_t>(Opcodes::OP_IMM), 0x1, 0x605) {}

void SEXTHInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1);
    int16_t HalfVal = static_cast<int16_t>(Rs1Val & 0xFFFF);
    int32_t Result = static_cast<int32_t>(HalfVal);
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

ZEXTHInstruction::ZEXTHInstruction() : UltraBitwiseITypeInstruction(static_cast<uint32_t>(Opcodes::OP_IMM), 0x4, 0x80) {}

void ZEXTHInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1);
    uint32_t Result = Rs1Val & 0xFFFF;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, static_cast<int32_t>(Result));
    TargetExecutor.getPC() += 4;
}

CLZInstruction::CLZInstruction() : UltraBitwiseITypeInstruction(static_cast<uint32_t>(Opcodes::OP_IMM), 0x1, 0x600) {}

void CLZInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = static_cast<uint32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1));
    int32_t LeadingZeros = 0;
    uint32_t LastBitMask = 0x80000000;
    Rs1Val = ~Rs1Val;
    for (size_t i = 0; i < sizeof(uint32_t) * 8; i++) {

        if (!(Rs1Val & LastBitMask))
            break;

        LeadingZeros++;
        Rs1Val <<= 1;
    }
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, LeadingZeros);
    TargetExecutor.getPC() += 4;
}

CTZInstruction::CTZInstruction() : UltraBitwiseITypeInstruction(static_cast<uint32_t>(Opcodes::OP_IMM), 0x1, 0x601) {}

void CTZInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = static_cast<uint32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1));
    int32_t TrailingZeros = 0;
    uint32_t FirstBitMask = 0x1;
    Rs1Val = ~Rs1Val;
    for (size_t i = 0; i < sizeof(uint32_t) * 8; i++) {

        if (!(Rs1Val & FirstBitMask))
            break;

        TrailingZeros++;
        Rs1Val >>= 1;
    }
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, TrailingZeros);
    TargetExecutor.getPC() += 4;
}

CPOPInstruction::CPOPInstruction() : UltraBitwiseITypeInstruction(static_cast<uint32_t>(Opcodes::OP_IMM), 0x1, 0x602) {}

void CPOPInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = static_cast<uint32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1));
    int32_t SetBits = 0;
    uint32_t FirstBitMask = 0x1;
    for (size_t i = 0; i < sizeof(uint32_t) * 8; i++) {

        if (!(Rs1Val & FirstBitMask))
            continue;

        SetBits++;
        Rs1Val >>= 1;
    }
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, SetBits);
    TargetExecutor.getPC() += 4;
}

RORIInstruction::RORIInstruction() : BitwiseITypeInstruction(static_cast<uint32_t>(Opcodes::OP_IMM), 0x5, 0x30) {}

void RORIInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = static_cast<uint32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1));
    uint32_t Shamt = Params.Imm & 0x1F;
    uint32_t Result = (Rs1Val >> Shamt) | (Rs1Val << (32 - Shamt));
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, static_cast<int32_t>(Result));
    TargetExecutor.getPC() += 4;
}

ORC_BInstruction::ORC_BInstruction() : UltraBitwiseITypeInstruction(static_cast<uint32_t>(Opcodes::OP_IMM), 0x5, 0x287) {}

void ORC_BInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = static_cast<uint32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1));
    int32_t Result = 0;
    for (size_t i = 0; i < sizeof(uint32_t) * 8; i += 8) {

        uint32_t CurrByte = ExtractBits(Rs1Val, i, i + 7);

        if (CurrByte == 0)
            continue;

        Result |= (0xFFu << i);
    }
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

REV8Instruction::REV8Instruction() : UltraBitwiseITypeInstruction(static_cast<uint32_t>(Opcodes::OP_IMM), 0x5, 0x698) {}

void REV8Instruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = static_cast<uint32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1));
    int32_t Result = 0;
    for (size_t i = 0, j = 24; i < sizeof(uint32_t) * 8; i += 8, j -= 8) {

        uint32_t CurrByte = ExtractBits(Rs1Val, i, i + 7);

        Result |= (CurrByte << j);
    }
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

void RV32ZbbExtension::registerInstructions() {
    registerRTypeInstructions();
    registerITypeInstructions();
}

void RV32ZbbExtension::registerRTypeInstructions() {
    addNewInstr(std::make_shared<ANDNInstruction>());
    addNewInstr(std::make_shared<ORNInstruction>());
    addNewInstr(std::make_shared<XNORInstruction>());
    addNewInstr(std::make_shared<MAXInstruction>());
    addNewInstr(std::make_shared<MAXUInstruction>());
    addNewInstr(std::make_shared<MINInstruction>());
    addNewInstr(std::make_shared<MINUInstruction>());
    addNewInstr(std::make_shared<ROLInstruction>());
    addNewInstr(std::make_shared<RORInstruction>());
}

void RV32ZbbExtension::registerITypeInstructions() {
    addNewInstr(std::make_shared<RORIInstruction>());
    addNewInstr(std::make_shared<SEXTBInstruction>());
    addNewInstr(std::make_shared<SEXTHInstruction>());
    addNewInstr(std::make_shared<ZEXTHInstruction>());
    addNewInstr(std::make_shared<CLZInstruction>());
    addNewInstr(std::make_shared<CTZInstruction>());
    addNewInstr(std::make_shared<CPOPInstruction>());
    addNewInstr(std::make_shared<ORC_BInstruction>());
    addNewInstr(std::make_shared<REV8Instruction>());
}

} // namespace r1scoviy
