#include "RV32ZBB.h"
#include "Simulator/SPU/Executor/Executor.h"
#include <memory>
#include <bit>

namespace r1scoviy {

// R-Type Instructions Implementation - Basic Bit Manipulation

// andn: Rd = Rs1 & ~Rs2
ANDNInstruction::ANDNInstruction() : RTypeInstruction(0x33, 0x4, 0x20) {}

void ANDNInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1);
    int32_t Rs2Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs2);
    int32_t Result = Rs1Val & ~Rs2Val;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

// orn: Rd = Rs1 | ~Rs2
ORNInstruction::ORNInstruction() : RTypeInstruction(0x33, 0x6, 0x20) {}

void ORNInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1);
    int32_t Rs2Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs2);
    int32_t Result = Rs1Val | ~Rs2Val;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

// xnor: Rd = Rs1 ^ ~Rs2 (equivalent to ~(Rs1 ^ Rs2))
XNORInstruction::XNORInstruction() : RTypeInstruction(0x33, 0x4, 0x21) {}

void XNORInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1);
    int32_t Rs2Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs2);
    int32_t Result = ~(Rs1Val ^ Rs2Val);
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

// max: Rd = signed(Rs1) > signed(Rs2) ? Rs1 : Rs2
MAXInstruction::MAXInstruction() : RTypeInstruction(0x33, 0x5, 0x20) {}

void MAXInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1);
    int32_t Rs2Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs2);
    int32_t Result = (Rs1Val > Rs2Val) ? Rs1Val : Rs2Val;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

// maxu: Rd = unsigned(Rs1) > unsigned(Rs2) ? Rs1 : Rs2
MAXUInstruction::MAXUInstruction() : RTypeInstruction(0x33, 0x5, 0x21) {}

void MAXUInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = static_cast<uint32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1));
    uint32_t Rs2Val = static_cast<uint32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs2));
    uint32_t Result = (Rs1Val > Rs2Val) ? Rs1Val : Rs2Val;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, static_cast<int32_t>(Result));
    TargetExecutor.getPC() += 4;
}

// min: Rd = signed(Rs1) < signed(Rs2) ? Rs1 : Rs2
MINInstruction::MINInstruction() : RTypeInstruction(0x33, 0x5, 0x22) {}

void MINInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1);
    int32_t Rs2Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs2);
    int32_t Result = (Rs1Val < Rs2Val) ? Rs1Val : Rs2Val;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

// minu: Rd = unsigned(Rs1) < unsigned(Rs2) ? Rs1 : Rs2
MINUInstruction::MINUInstruction() : RTypeInstruction(0x33, 0x5, 0x23) {}

void MINUInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = static_cast<uint32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1));
    uint32_t Rs2Val = static_cast<uint32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs2));
    uint32_t Result = (Rs1Val < Rs2Val) ? Rs1Val : Rs2Val;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, static_cast<int32_t>(Result));
    TargetExecutor.getPC() += 4;
}

// rol: Rd = Rs1 <<< (Rs2 & 0x1F) - Rotate Left
ROLInstruction::ROLInstruction() : RTypeInstruction(0x33, 0x1, 0x21) {}

void ROLInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = static_cast<uint32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1));
    int32_t Rs2Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs2);
    uint32_t Shamt = Rs2Val & 0x1F;
    uint32_t Result = (Rs1Val << Shamt) | (Rs1Val >> (32 - Shamt));
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, static_cast<int32_t>(Result));
    TargetExecutor.getPC() += 4;
}

// ror: Rd = Rs1 >>> (Rs2 & 0x1F) - Rotate Right
RORInstruction::RORInstruction() : RTypeInstruction(0x33, 0x5, 0x21) {}

void RORInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = static_cast<uint32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1));
    int32_t Rs2Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs2);
    uint32_t Shamt = Rs2Val & 0x1F;
    uint32_t Result = (Rs1Val >> Shamt) | (Rs1Val << (32 - Shamt));
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, static_cast<int32_t>(Result));
    TargetExecutor.getPC() += 4;
}

// sext.b: Rd = sign_extend(Rs1[7:0])
SEXTBInstruction::SEXTBInstruction() : RTypeInstruction(0x33, 0x5, 0x24) {}

void SEXTBInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1);
    int8_t ByteVal = static_cast<int8_t>(Rs1Val & 0xFF);
    int32_t Result = static_cast<int32_t>(ByteVal);
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

// sext.h: Rd = sign_extend(Rs1[15:0])
SEXTHInstruction::SEXTHInstruction() : RTypeInstruction(0x33, 0x5, 0x25) {}

void SEXTHInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1);
    int16_t HalfVal = static_cast<int16_t>(Rs1Val & 0xFFFF);
    int32_t Result = static_cast<int32_t>(HalfVal);
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

// zext.b: Rd = zero_extend(Rs1[7:0])
ZEXTBInstruction::ZEXTBInstruction() : RTypeInstruction(0x33, 0x4, 0x24) {}

void ZEXTBInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1);
    uint32_t Result = Rs1Val & 0xFF;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, static_cast<int32_t>(Result));
    TargetExecutor.getPC() += 4;
}

// zext.h: Rd = zero_extend(Rs1[15:0])
ZEXTHInstruction::ZEXTHInstruction() : RTypeInstruction(0x33, 0x4, 0x25) {}

void ZEXTHInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1);
    uint32_t Result = Rs1Val & 0xFFFF;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, static_cast<int32_t>(Result));
    TargetExecutor.getPC() += 4;
}

// clz: Rd = count leading zeros in Rs1
CLZInstruction::CLZInstruction() : RTypeInstruction(0x33, 0x1, 0x20) {}

void CLZInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = static_cast<uint32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1));
    int32_t Result = std::countl_zero(Rs1Val);
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

// ctz: Rd = count trailing zeros in Rs1
CTZInstruction::CTZInstruction() : RTypeInstruction(0x33, 0x1, 0x22) {}

void CTZInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = static_cast<uint32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1));
    int32_t Result = std::countl_zero(static_cast<uint32_t>(std::countr_zero(Rs1Val)));
    if (Rs1Val == 0) {
        Result = 32;
    } else {
        Result = std::countr_zero(Rs1Val);
    }
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

// cpop: Rd = population count of Rs1
CPOPInstruction::CPOPInstruction() : RTypeInstruction(0x33, 0x1, 0x23) {}

void CPOPInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = static_cast<uint32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1));
    int32_t Result = std::popcount(Rs1Val);
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

// I-Type Instructions Implementation

// rori: Rd = Rs1 >>> shamt (rotate right by immediate)
RORIInstruction::RORIInstruction() : BitwiseITypeInstruction(0x13, 0x5, 0x20) {}

void RORIInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = static_cast<uint32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1));
    uint32_t Shamt = Params.Imm & 0x1F;
    uint32_t Result = (Rs1Val >> Shamt) | (Rs1Val << (32 - Shamt));
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, static_cast<int32_t>(Result));
    TargetExecutor.getPC() += 4;
}

// Extension Registration

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
    addNewInstr(std::make_shared<SEXTBInstruction>());
    addNewInstr(std::make_shared<SEXTHInstruction>());
    addNewInstr(std::make_shared<ZEXTBInstruction>());
    addNewInstr(std::make_shared<ZEXTHInstruction>());
    addNewInstr(std::make_shared<CLZInstruction>());
    addNewInstr(std::make_shared<CTZInstruction>());
    addNewInstr(std::make_shared<CPOPInstruction>());
}

void RV32ZbbExtension::registerITypeInstructions() {
    addNewInstr(std::make_shared<RORIInstruction>());
}

} // namespace r1scoviy
