#include <cmath>
#include <cstdint>
#include <cstring>
#include <limits>

#include "RV32F.h"
#include "MathHelper/MathHelper.h"
#include "Simulator/SPU/Executor/InstructionDispatcher.h"
#include "Simulator/SPU/Executor/Executor.h"
#include <memory>

namespace r1scoviy {

// Helper function to read float from register file (stored as int32_t bit pattern)
static float ReadFloatReg(RegisterFileUnit &RegisterFile, uint32_t RegNum) {
    int32_t Bits = RegisterFile.readRegister(RegistersType::FLOAT_REGS, RegNum);
    float Result;
    std::memcpy(&Result, &Bits, sizeof(float));
    return Result;
}

// Helper function to write float to register file (stored as int32_t bit pattern)
static void WriteFloatReg(RegisterFileUnit &RegisterFile, uint32_t RegNum, float Value) {
    if (RegNum == 0) return;
    int32_t Bits;
    std::memcpy(&Bits, &Value, sizeof(float));
    RegisterFile.writeRegister(RegistersType::FLOAT_REGS, RegNum, Bits);
}

// Load/Store Instructions Implementation

FLWInstruction::FLWInstruction() : ITypeInstruction(0x7, 0x2) {}

void FLWInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1);
    uint32_t Addr = static_cast<uint32_t>(Rs1Val + getSignExtImm(Params.Imm));
    uint32_t Word = TargetExecutor.getRAMController().loadWord(Addr);
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::FLOAT_REGS, Params.Rd, static_cast<int32_t>(Word));
    TargetExecutor.getPC() += 4;
}

FSWInstruction::FSWInstruction() : STypeInstruction(0x27, 0x2) {}

void FSWInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1);
    int32_t Rs2Bits = TargetExecutor.getRegisterFile().readRegister(RegistersType::FLOAT_REGS, Params.Rs2);
    uint32_t Addr = static_cast<uint32_t>(Rs1Val + getSignExtImm(Params.Imm));
    TargetExecutor.getRAMController().storeWord(Addr, static_cast<uint32_t>(Rs2Bits));
    TargetExecutor.getPC() += 4;
}

// Arithmetic Instructions Implementation

FADD_SInstruction::FADD_SInstruction() : RTypeInstruction(0x53, 0x0, 0x0) {}

void FADD_SInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    float Rs1Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs1);
    float Rs2Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs2);
    float Result = Rs1Val + Rs2Val;
    WriteFloatReg(TargetExecutor.getRegisterFile(), Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

FSUB_SInstruction::FSUB_SInstruction() : RTypeInstruction(0x53, 0x0, 0x8) {}

void FSUB_SInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    float Rs1Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs1);
    float Rs2Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs2);
    float Result = Rs1Val - Rs2Val;
    WriteFloatReg(TargetExecutor.getRegisterFile(), Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

FMUL_SInstruction::FMUL_SInstruction() : RTypeInstruction(0x53, 0x0, 0x10) {}

void FMUL_SInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    float Rs1Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs1);
    float Rs2Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs2);
    float Result = Rs1Val * Rs2Val;
    WriteFloatReg(TargetExecutor.getRegisterFile(), Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

FDIV_SInstruction::FDIV_SInstruction() : RTypeInstruction(0x53, 0x0, 0x18) {}

void FDIV_SInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    float Rs1Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs1);
    float Rs2Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs2);
    float Result = Rs1Val / Rs2Val;
    WriteFloatReg(TargetExecutor.getRegisterFile(), Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

FSQRT_SInstruction::FSQRT_SInstruction() : RTypeInstruction(0x53, 0x0, 0x58) {}

void FSQRT_SInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    float Rs1Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs1);
    float Result = std::sqrt(Rs1Val);
    WriteFloatReg(TargetExecutor.getRegisterFile(), Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

FSGNJ_SInstruction::FSGNJ_SInstruction() : RTypeInstruction(0x53, 0x0, 0x20) {}

void FSGNJ_SInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Bits = TargetExecutor.getRegisterFile().readRegister(RegistersType::FLOAT_REGS, Params.Rs1);
    int32_t Rs2Bits = TargetExecutor.getRegisterFile().readRegister(RegistersType::FLOAT_REGS, Params.Rs2);
    uint32_t SignMask = 0x80000000;
    uint32_t MagnitudeMask = 0x7FFFFFFF;
    int32_t Result = (Rs2Bits & SignMask) | (Rs1Bits & MagnitudeMask);
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::FLOAT_REGS, Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

FSGNJN_SInstruction::FSGNJN_SInstruction() : RTypeInstruction(0x53, 0x0, 0x21) {}

void FSGNJN_SInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Bits = TargetExecutor.getRegisterFile().readRegister(RegistersType::FLOAT_REGS, Params.Rs1);
    int32_t Rs2Bits = TargetExecutor.getRegisterFile().readRegister(RegistersType::FLOAT_REGS, Params.Rs2);
    uint32_t SignMask = 0x80000000;
    uint32_t MagnitudeMask = 0x7FFFFFFF;
    int32_t Result = ((~Rs2Bits) & SignMask) | (Rs1Bits & MagnitudeMask);
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::FLOAT_REGS, Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

FSGNJX_SInstruction::FSGNJX_SInstruction() : RTypeInstruction(0x53, 0x0, 0x22) {}

void FSGNJX_SInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Bits = TargetExecutor.getRegisterFile().readRegister(RegistersType::FLOAT_REGS, Params.Rs1);
    int32_t Rs2Bits = TargetExecutor.getRegisterFile().readRegister(RegistersType::FLOAT_REGS, Params.Rs2);
    uint32_t SignMask = 0x80000000;
    uint32_t MagnitudeMask = 0x7FFFFFFF;
    int32_t Result = ((Rs1Bits ^ Rs2Bits) & SignMask) | (Rs1Bits & MagnitudeMask);
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::FLOAT_REGS, Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

FMIN_SInstruction::FMIN_SInstruction() : RTypeInstruction(0x53, 0x0, 0x28) {}

void FMIN_SInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    float Rs1Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs1);
    float Rs2Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs2);
    float Result = std::fmin(Rs1Val, Rs2Val);
    WriteFloatReg(TargetExecutor.getRegisterFile(), Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

FMAX_SInstruction::FMAX_SInstruction() : RTypeInstruction(0x53, 0x0, 0x29) {}

void FMAX_SInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    float Rs1Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs1);
    float Rs2Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs2);
    float Result = std::fmax(Rs1Val, Rs2Val);
    WriteFloatReg(TargetExecutor.getRegisterFile(), Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

// Conversion Instructions Implementation

FCVT_W_SInstruction::FCVT_W_SInstruction() : RTypeInstruction(0x53, 0x0, 0xC0) {}

void FCVT_W_SInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    float Rs1Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs1);
    int32_t Result = static_cast<int32_t>(Rs1Val);
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

FCVT_WU_SInstruction::FCVT_WU_SInstruction() : RTypeInstruction(0x53, 0x0, 0xC1) {}

void FCVT_WU_SInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    float Rs1Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs1);
    uint32_t Result = static_cast<uint32_t>(Rs1Val);
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, static_cast<int32_t>(Result));
    TargetExecutor.getPC() += 4;
}

FCVT_S_WInstruction::FCVT_S_WInstruction() : RTypeInstruction(0x53, 0x0, 0xD0) {}

void FCVT_S_WInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1);
    float Result = static_cast<float>(Rs1Val);
    WriteFloatReg(TargetExecutor.getRegisterFile(), Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

FCVT_S_WUInstruction::FCVT_S_WUInstruction() : RTypeInstruction(0x53, 0x0, 0xD1) {}

void FCVT_S_WUInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = static_cast<uint32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1));
    float Result = static_cast<float>(Rs1Val);
    WriteFloatReg(TargetExecutor.getRegisterFile(), Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

FMV_X_WInstruction::FMV_X_WInstruction() : RTypeInstruction(0x53, 0x0, 0xE0) {}

void FMV_X_WInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Bits = TargetExecutor.getRegisterFile().readRegister(RegistersType::FLOAT_REGS, Params.Rs1);
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, Rs1Bits);
    TargetExecutor.getPC() += 4;
}

FMV_W_XInstruction::FMV_W_XInstruction() : RTypeInstruction(0x53, 0x0, 0xF0) {}

void FMV_W_XInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1);
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::FLOAT_REGS, Params.Rd, Rs1Val);
    TargetExecutor.getPC() += 4;
}

// Comparison Instructions Implementation

FEQ_SInstruction::FEQ_SInstruction() : RTypeInstruction(0x53, 0x0, 0x50) {}

void FEQ_SInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    float Rs1Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs1);
    float Rs2Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs2);
    int32_t Result = (Rs1Val == Rs2Val) ? 1 : 0;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

FLT_SInstruction::FLT_SInstruction() : RTypeInstruction(0x53, 0x0, 0x51) {}

void FLT_SInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    float Rs1Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs1);
    float Rs2Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs2);
    int32_t Result = (Rs1Val < Rs2Val) ? 1 : 0;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

FLE_SInstruction::FLE_SInstruction() : RTypeInstruction(0x53, 0x0, 0x52) {}

void FLE_SInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    float Rs1Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs1);
    float Rs2Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs2);
    int32_t Result = (Rs1Val <= Rs2Val) ? 1 : 0;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

FCLASS_SInstruction::FCLASS_SInstruction() : RTypeInstruction(0x53, 0x0, 0xA0) {}

void FCLASS_SInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    float Rs1Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs1);
    
    int32_t Result = 0;
    
    if (std::isnan(Rs1Val)) {
        if (std::signbit(Rs1Val)) {
            Result |= (1 << 9);
        } else {
            Result |= (1 << 8);
        }
    } else if (std::isinf(Rs1Val)) {
        if (std::signbit(Rs1Val)) {
            Result |= (1 << 0);
        } else {
            Result |= (1 << 7);
        }
    } else if (Rs1Val == 0.0f) {
        if (std::signbit(Rs1Val)) {
            Result |= (1 << 1);
        } else {
            Result |= (1 << 6);
        }
    } else if (std::fpclassify(Rs1Val) == FP_SUBNORMAL) {
        if (std::signbit(Rs1Val)) {
            Result |= (1 << 2);
        } else {
            Result |= (1 << 5);
        }
    } else {
        if (Rs1Val < 0.0f) {
            Result |= (1 << 3);
        } else {
            Result |= (1 << 4);
        }
    }
    
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

// Extension Registration

void RV32FExtension::registerInstructions() {
    registerLoadStoreInstructions();
    registerArithmeticInstructions();
    registerConversionInstructions();
    registerComparisonInstructions();
}

void RV32FExtension::registerLoadStoreInstructions() {
    addNewInstr(std::make_shared<FLWInstruction>());
    addNewInstr(std::make_shared<FSWInstruction>());
}

void RV32FExtension::registerArithmeticInstructions() {
    addNewInstr(std::make_shared<FADD_SInstruction>());
    addNewInstr(std::make_shared<FSUB_SInstruction>());
    addNewInstr(std::make_shared<FMUL_SInstruction>());
    addNewInstr(std::make_shared<FDIV_SInstruction>());
    addNewInstr(std::make_shared<FSQRT_SInstruction>());
    addNewInstr(std::make_shared<FSGNJ_SInstruction>());
    addNewInstr(std::make_shared<FSGNJN_SInstruction>());
    addNewInstr(std::make_shared<FSGNJX_SInstruction>());
    addNewInstr(std::make_shared<FMIN_SInstruction>());
    addNewInstr(std::make_shared<FMAX_SInstruction>());
}

void RV32FExtension::registerConversionInstructions() {
    addNewInstr(std::make_shared<FCVT_W_SInstruction>());
    addNewInstr(std::make_shared<FCVT_WU_SInstruction>());
    addNewInstr(std::make_shared<FCVT_S_WInstruction>());
    addNewInstr(std::make_shared<FCVT_S_WUInstruction>());
    addNewInstr(std::make_shared<FMV_X_WInstruction>());
    addNewInstr(std::make_shared<FMV_W_XInstruction>());
}

void RV32FExtension::registerComparisonInstructions() {
    addNewInstr(std::make_shared<FEQ_SInstruction>());
    addNewInstr(std::make_shared<FLT_SInstruction>());
    addNewInstr(std::make_shared<FLE_SInstruction>());
    addNewInstr(std::make_shared<FCLASS_SInstruction>());
}

} // namespace r1scoviy
