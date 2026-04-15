#include <unistd.h>

#include "RV32I.h"
#include "src/Simulator/SPU/Executor/InstructionDispatcher.h"
#include "src/Simulator/SPU/Executor/Executor.h"
#include <memory>

namespace r1scoviy {

// R-Type Instructions Implementation

ADDInstruction::ADDInstruction() : RTypeInstruction(0x33, 0x0, 0x0) {}

void ADDInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs1));
    uint32_t Rs2Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs2));
    uint32_t Result = Rs1Val + Rs2Val;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rd), Result);
}

SUBInstruction::SUBInstruction() : RTypeInstruction(0x33, 0x0, 0x20) {}

void SUBInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs1));
    uint32_t Rs2Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs2));
    uint32_t Result = Rs1Val - Rs2Val;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rd), Result);
}

SLLInstruction::SLLInstruction() : RTypeInstruction(0x33, 0x1, 0x0) {}

void SLLInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs1));
    uint32_t Rs2Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs2));
    uint32_t Shamt = Rs2Val & 0x1F;
    uint32_t Result = Rs1Val << Shamt;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rd), Result);
}

SLTInstruction::SLTInstruction() : RTypeInstruction(0x33, 0x2, 0x0) {}

void SLTInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Val = static_cast<int32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs1)));
    int32_t Rs2Val = static_cast<int32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs2)));
    uint32_t Result = (Rs1Val < Rs2Val) ? 1 : 0;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rd), Result);
}

SLTUInstruction::SLTUInstruction() : RTypeInstruction(0x33, 0x3, 0x0) {}

void SLTUInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs1));
    uint32_t Rs2Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs2));
    uint32_t Result = (Rs1Val < Rs2Val) ? 1 : 0;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rd), Result);
}

XORInstruction::XORInstruction() : RTypeInstruction(0x33, 0x4, 0x0) {}

void XORInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs1));
    uint32_t Rs2Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs2));
    uint32_t Result = Rs1Val ^ Rs2Val;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rd), Result);
}

SRLInstruction::SRLInstruction() : RTypeInstruction(0x33, 0x5, 0x0) {}

void SRLInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs1));
    uint32_t Rs2Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs2));
    uint32_t Shamt = Rs2Val & 0x1F;
    uint32_t Result = Rs1Val >> Shamt;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rd), Result);
}

SRAInstruction::SRAInstruction() : RTypeInstruction(0x33, 0x5, 0x20) {}

void SRAInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Val = static_cast<int32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs1)));
    uint32_t Rs2Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs2));
    uint32_t Shamt = Rs2Val & 0x1F;
    int32_t Result = Rs1Val >> Shamt;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rd), static_cast<uint32_t>(Result));
}

ORInstruction::ORInstruction() : RTypeInstruction(0x33, 0x6, 0x0) {}

void ORInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs1));
    uint32_t Rs2Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs2));
    uint32_t Result = Rs1Val | Rs2Val;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rd), Result);
}

ANDInstruction::ANDInstruction() : RTypeInstruction(0x33, 0x7, 0x0) {}

void ANDInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs1));
    uint32_t Rs2Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs2));
    uint32_t Result = Rs1Val & Rs2Val;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rd), Result);
}

// I-Type Instructions Implementation

ADDIInstruction::ADDIInstruction() : ITypeInstruction(0x13, 0x0) {}

void ADDIInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Val = static_cast<int32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs1)));
    int32_t ImmVal = static_cast<int32_t>(Params.Imm);
    int32_t Result = Rs1Val + ImmVal;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rd), static_cast<uint32_t>(Result));
}

SLTIInstruction::SLTIInstruction() : ITypeInstruction(0x13, 0x2) {}

void SLTIInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Val = static_cast<int32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs1)));
    int32_t ImmVal = static_cast<int32_t>(Params.Imm);
    uint32_t Result = (Rs1Val < ImmVal) ? 1 : 0;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rd), Result);
}

SLTIUInstruction::SLTIUInstruction() : ITypeInstruction(0x13, 0x3) {}

void SLTIUInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs1));
    uint32_t ImmVal = static_cast<uint32_t>(static_cast<int32_t>(Params.Imm));
    uint32_t Result = (Rs1Val < ImmVal) ? 1 : 0;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rd), Result);
}

XORIInstruction::XORIInstruction() : ITypeInstruction(0x13, 0x4) {}

void XORIInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs1));
    uint32_t ImmVal = static_cast<uint32_t>(static_cast<int32_t>(Params.Imm));
    uint32_t Result = Rs1Val ^ ImmVal;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rd), Result);
}

ORIInstruction::ORIInstruction() : ITypeInstruction(0x13, 0x6) {}

void ORIInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs1));
    uint32_t ImmVal = static_cast<uint32_t>(static_cast<int32_t>(Params.Imm));
    uint32_t Result = Rs1Val | ImmVal;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rd), Result);
}

ANDIInstruction::ANDIInstruction() : ITypeInstruction(0x13, 0x7) {}

void ANDIInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs1));
    uint32_t ImmVal = static_cast<uint32_t>(static_cast<int32_t>(Params.Imm));
    uint32_t Result = Rs1Val & ImmVal;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rd), Result);
}

SLLIInstruction::SLLIInstruction() : BitwiseITypeInstruction(0x13, 0x1, 0x0) {}

void SLLIInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs1));
    uint32_t Shamt = Params.Imm & 0x1F;
    uint32_t Result = Rs1Val << Shamt;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rd), Result);
}

SRLIInstruction::SRLIInstruction() : BitwiseITypeInstruction(0x13, 0x5, 0x0) {}

void SRLIInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs1));
    uint32_t Shamt = Params.Imm & 0x1F;
    uint32_t Result = Rs1Val >> Shamt;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rd), Result);
}

SRAIInstruction::SRAIInstruction() : BitwiseITypeInstruction(0x13, 0x5, 0x20) {}

void SRAIInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Val = static_cast<int32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs1)));
    uint32_t Shamt = Params.Imm & 0x1F;
    int32_t Result = Rs1Val >> Shamt;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rd), static_cast<uint32_t>(Result));
}

LBInstruction::LBInstruction() : ITypeInstruction(0x3, 0x0) {}

void LBInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Addr = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs1)) + static_cast<uint32_t>(static_cast<int32_t>(Params.Imm));
    uint8_t Byte = TargetExecutor.getRAMController().getByte(Addr);
    int8_t SignExtended = static_cast<int8_t>(Byte);
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rd), static_cast<uint32_t>(SignExtended));
}

LHInstruction::LHInstruction() : ITypeInstruction(0x3, 0x1) {}

void LHInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Addr = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs1)) + static_cast<uint32_t>(static_cast<int32_t>(Params.Imm));
    uint16_t Halfword = TargetExecutor.getRAMController().getHalfword(Addr);
    int16_t SignExtended = static_cast<int16_t>(Halfword);
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rd), static_cast<uint32_t>(SignExtended));
}

LWInstruction::LWInstruction() : ITypeInstruction(0x3, 0x2) {}

void LWInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Addr = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs1)) + static_cast<uint32_t>(static_cast<int32_t>(Params.Imm));
    uint32_t Word = TargetExecutor.getRAMController().getWord(Addr);
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rd), Word);
}

LBUInstruction::LBUInstruction() : ITypeInstruction(0x3, 0x4) {}

void LBUInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Addr = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs1)) + static_cast<uint32_t>(static_cast<int32_t>(Params.Imm));
    uint8_t Byte = TargetExecutor.getRAMController().getByte(Addr);
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rd), static_cast<uint32_t>(Byte));
}

LHUInstruction::LHUInstruction() : ITypeInstruction(0x3, 0x5) {}

void LHUInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Addr = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs1)) + static_cast<uint32_t>(static_cast<int32_t>(Params.Imm));
    uint16_t Halfword = TargetExecutor.getRAMController().getHalfword(Addr);
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rd), static_cast<uint32_t>(Halfword));
}

JALRInstruction::JALRInstruction() : ITypeInstruction(0x67, 0x0) {}

void JALRInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Pc = TargetExecutor.getPC();
    uint32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs1));
    uint32_t TargetAddr = (Rs1Val + static_cast<uint32_t>(static_cast<int32_t>(Params.Imm))) & ~1U;

    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rd), Pc + 4);
    TargetExecutor.getPC() = TargetAddr;
}

ECALLInstruction::ECALLInstruction() : ITypeInstruction(0x73, 0x0) {}

void ECALLInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    
    int A7Num = 17;
    int32_t SyscallNum = static_cast<int32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(A7Num)));
    
    if (SyscallNum == 93) {
        
        // TODO: TargetExecutor.getSpuStatus = STOP;
        return;
    }

    int A0Num = 10;
    int A2Num = 12;
    int A3Num = 13;

    uint32_t A0Val = static_cast<uint32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(A0Num)));
    uint32_t A2Val = static_cast<uint32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(A2Num)));
    uint32_t A3Val = static_cast<uint32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(A3Num)));

    if (SyscallNum == 63) {

        read(static_cast<int>(A0Val), reinterpret_cast<void *>(A2Val), A3Val);
    }
    if (SyscallNum == 64) {
        
        write(static_cast<int>(A0Val), reinterpret_cast<void *>(A2Val), A3Val);
    }
}

// S-Type Instructions Implementation

SBInstruction::SBInstruction() : STypeInstruction(0x23, 0x0) {}

void SBInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs1));
    uint32_t Rs2Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs2));
    uint32_t Addr = Rs1Val + static_cast<uint32_t>(static_cast<int32_t>(Params.Imm));
    uint8_t Byte = static_cast<uint8_t>(Rs2Val & 0xFF);
    TargetExecutor.getRAMController().storeByte(Addr, Byte);
}

SHInstruction::SHInstruction() : STypeInstruction(0x23, 0x1) {}

void SHInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs1));
    uint32_t Rs2Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs2));
    uint32_t Addr = Rs1Val + static_cast<uint32_t>(static_cast<int32_t>(Params.Imm));
    uint16_t Halfword = static_cast<uint16_t>(Rs2Val & 0xFFFF);
    TargetExecutor.getRAMController().storeHalfword(Addr, Halfword);
}

SWInstruction::SWInstruction() : STypeInstruction(0x23, 0x2) {}

void SWInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs1));
    uint32_t Rs2Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs2));
    uint32_t Addr = Rs1Val + static_cast<uint32_t>(static_cast<int32_t>(Params.Imm));
    TargetExecutor.getRAMController().storeWord(Addr, Rs2Val);
}

// B-Type Instructions Implementation

BEQInstruction::BEQInstruction() : BTypeInstruction(0x63, 0x0) {}

void BEQInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs1));
    uint32_t Rs2Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs2));

    if (Rs1Val == Rs2Val) {
        uint32_t Pc = TargetExecutor.getPC();
        uint32_t TargetAddr = Pc + static_cast<uint32_t>(static_cast<int32_t>(Params.Imm));
        TargetExecutor.getPC() = TargetAddr;
    } else {
        TargetExecutor.getPC() += 4;
    }
}

BNEInstruction::BNEInstruction() : BTypeInstruction(0x63, 0x1) {}

void BNEInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs1));
    uint32_t Rs2Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs2));

    if (Rs1Val != Rs2Val) {
        uint32_t Pc = TargetExecutor.getPC();
        uint32_t TargetAddr = Pc + static_cast<uint32_t>(static_cast<int32_t>(Params.Imm));
        TargetExecutor.getPC() = TargetAddr;
    } else {
        TargetExecutor.getPC() += 4;
    }
}

BLTInstruction::BLTInstruction() : BTypeInstruction(0x63, 0x4) {}

void BLTInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Val = static_cast<int32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs1)));
    int32_t Rs2Val = static_cast<int32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs2)));

    if (Rs1Val < Rs2Val) {
        uint32_t Pc = TargetExecutor.getPC();
        uint32_t TargetAddr = Pc + static_cast<uint32_t>(static_cast<int32_t>(Params.Imm));
        TargetExecutor.getPC() = TargetAddr;
    } else {
        TargetExecutor.getPC() += 4;
    }
}

BGEInstruction::BGEInstruction() : BTypeInstruction(0x63, 0x5) {}

void BGEInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Val = static_cast<int32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs1)));
    int32_t Rs2Val = static_cast<int32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs2)));

    if (Rs1Val >= Rs2Val) {
        uint32_t Pc = TargetExecutor.getPC();
        uint32_t TargetAddr = Pc + static_cast<uint32_t>(static_cast<int32_t>(Params.Imm));
        TargetExecutor.getPC() = TargetAddr;
    } else {
        TargetExecutor.getPC() += 4;
    }
}

BLTUInstruction::BLTUInstruction() : BTypeInstruction(0x63, 0x6) {}

void BLTUInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs1));
    uint32_t Rs2Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs2));

    if (Rs1Val < Rs2Val) {
        uint32_t Pc = TargetExecutor.getPC();
        uint32_t TargetAddr = Pc + static_cast<uint32_t>(static_cast<int32_t>(Params.Imm));
        TargetExecutor.getPC() = TargetAddr;
    } else {
        TargetExecutor.getPC() += 4;
    }
}

BGEUInstruction::BGEUInstruction() : BTypeInstruction(0x63, 0x7) {}

void BGEUInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs1));
    uint32_t Rs2Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rs2));

    if (Rs1Val >= Rs2Val) {
        uint32_t Pc = TargetExecutor.getPC();
        uint32_t TargetAddr = Pc + static_cast<uint32_t>(static_cast<int32_t>(Params.Imm));
        TargetExecutor.getPC() = TargetAddr;
    } else {
        TargetExecutor.getPC() += 4;
    }
}

// U-Type Instructions Implementation

LUIInstruction::LUIInstruction() : UTypeInstruction(0x37) {}

void LUIInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Result = static_cast<uint32_t>(Params.Imm) << 12;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rd), Result);
}

AUIPCInstruction::AUIPCInstruction() : UTypeInstruction(0x17) {}

void AUIPCInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Pc = TargetExecutor.getPC();
    uint32_t Result = Pc + (static_cast<uint32_t>(Params.Imm) << 12);
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rd), Result);
}

// J-Type Instructions Implementation

JALInstruction::JALInstruction() : JTypeInstruction(0x6F) {}

void JALInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Pc = TargetExecutor.getPC();
    uint32_t TargetAddr = Pc + static_cast<uint32_t>(static_cast<int32_t>(Params.Imm));

    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, static_cast<uint32_t>(Params.Rd), Pc + 4);
    TargetExecutor.getPC() = TargetAddr;
}

void RV32IExtension::registerInstructions() {
    registerRTypeInstructions();
    registerITypeInstructions();
    registerSTypeInstructions();
    registerBTypeInstructions();
    registerUTypeInstructions();
    registerJTypeInstructions();
}

void RV32IExtension::registerRTypeInstructions() {
    addNewInstr(std::make_shared<ADDInstruction>());
    addNewInstr(std::make_shared<SUBInstruction>());
    addNewInstr(std::make_shared<SLLInstruction>());
    addNewInstr(std::make_shared<SLTInstruction>());
    addNewInstr(std::make_shared<SLTUInstruction>());
    addNewInstr(std::make_shared<XORInstruction>());
    addNewInstr(std::make_shared<SRLInstruction>());
    addNewInstr(std::make_shared<SRAInstruction>());
    addNewInstr(std::make_shared<ORInstruction>());
    addNewInstr(std::make_shared<ANDInstruction>());
}

void RV32IExtension::registerITypeInstructions() {
    addNewInstr(std::make_shared<ADDIInstruction>());
    addNewInstr(std::make_shared<SLTIInstruction>());
    addNewInstr(std::make_shared<SLTIUInstruction>());
    addNewInstr(std::make_shared<XORIInstruction>());
    addNewInstr(std::make_shared<ORIInstruction>());
    addNewInstr(std::make_shared<ANDIInstruction>());
    addNewInstr(std::make_shared<SLLIInstruction>());
    addNewInstr(std::make_shared<SRLIInstruction>());
    addNewInstr(std::make_shared<SRAIInstruction>());
    addNewInstr(std::make_shared<LBInstruction>());
    addNewInstr(std::make_shared<LHInstruction>());
    addNewInstr(std::make_shared<LWInstruction>());
    addNewInstr(std::make_shared<LBUInstruction>());
    addNewInstr(std::make_shared<LHUInstruction>());
    addNewInstr(std::make_shared<JALRInstruction>());
    addNewInstr(std::make_shared<ECALLInstruction>());
}

void RV32IExtension::registerSTypeInstructions() {
    addNewInstr(std::make_shared<SBInstruction>());
    addNewInstr(std::make_shared<SHInstruction>());
    addNewInstr(std::make_shared<SWInstruction>());
}

void RV32IExtension::registerBTypeInstructions() {
    addNewInstr(std::make_shared<BEQInstruction>());
    addNewInstr(std::make_shared<BNEInstruction>());
    addNewInstr(std::make_shared<BLTInstruction>());
    addNewInstr(std::make_shared<BGEInstruction>());
    addNewInstr(std::make_shared<BLTUInstruction>());
    addNewInstr(std::make_shared<BGEUInstruction>());
}

void RV32IExtension::registerUTypeInstructions() {
    addNewInstr(std::make_shared<LUIInstruction>());
    addNewInstr(std::make_shared<AUIPCInstruction>());
}

void RV32IExtension::registerJTypeInstructions() {
    addNewInstr(std::make_shared<JALInstruction>());
}

} // namespace r1scoviy
