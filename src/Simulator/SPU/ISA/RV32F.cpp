#include <OverwriteMacros.h>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <memory>
#include <cassert>

extern "C" {
    #include "softfloat.h"
    #include "internals.h"
    #include "specialize.h"
}

#include "RV32F.h"
#include "MathHelper/MathHelper.h"
#include "Simulator/SPU/Executor/Executor.h"
#include "Simulator/SPU/ISA/InstructionTypes.h"

namespace r1scoviy {

// Exceptions are not for us

static uint32_t Fcsr = 0;

static uint32_t RiscvToSoftfloatRm(uint32_t RmBits) {
    
    RV32FRounding Rm = static_cast<RV32FRounding>(RmBits);

    if (Rm == RV32FRounding::DYN)
        Rm = static_cast<RV32FRounding>(ExtractBits(Fcsr, 5, 7));

    switch (Rm) {
        case RV32FRounding::RNE: return softfloat_round_near_even; // RNE
        case RV32FRounding::RTZ: return softfloat_round_minMag;      // RTZ
        case RV32FRounding::RDN: return softfloat_round_min;         // RDN
        case RV32FRounding::RUP: return softfloat_round_max;           // RUP
        case RV32FRounding::RMM: return softfloat_round_near_maxMag; // RMM (handled separately)
        case RV32FRounding::DYN: {

            LOG_ERROR_("RiscvToSoftfloatRm: DYN rounding mode inside switch-case!");

            assert(0);
        }
        default: {
            
            LOG_ERROR_("RiscvToSoftfloatRm: wrong risc-v rounding mode ({})!", static_cast<int32_t>(Rm));
            
            assert(0);
        }
    }

    // return default mode if conversion fails
    return softfloat_round_near_even;
}

static float32_t ReadFloatReg(RegisterFileUnit &RegisterFile, int RegNum) {

    int32_t Value = RegisterFile.readRegister(RegistersType::FLOAT_REGS, RegNum);
    
    float32_t FloatVal = {};
    FloatVal.v = Value;

    return FloatVal;
}

static void WriteFloatReg(RegisterFileUnit &RegisterFile, int RegNum, float32_t Value) {

    RegisterFile.writeRegister(RegistersType::FLOAT_REGS, RegNum, Value.v);
}

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

FADD_SInstruction::FADD_SInstruction() : FloatTypeRoundingInstruction(static_cast<uint32_t>(Opcodes::OP_FP), 0x0) {}

void FADD_SInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    float32_t Rs1Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs1);
    float32_t Rs2Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs2);
    softfloat_roundingMode = RiscvToSoftfloatRm(Params.Rm);
    float32_t Result = f32_add(Rs1Val, Rs2Val);
    WriteFloatReg(TargetExecutor.getRegisterFile(), Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

FSUB_SInstruction::FSUB_SInstruction() : FloatTypeRoundingInstruction(static_cast<uint32_t>(Opcodes::OP_FP), 0x1) {}

void FSUB_SInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    float32_t Rs1Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs1);
    float32_t Rs2Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs2);
    softfloat_roundingMode = RiscvToSoftfloatRm(Params.Rm);
    float32_t Result = f32_sub(Rs1Val, Rs2Val);
    WriteFloatReg(TargetExecutor.getRegisterFile(), Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

FMUL_SInstruction::FMUL_SInstruction() : FloatTypeRoundingInstruction(static_cast<uint32_t>(Opcodes::OP_FP), 0x2) {}

void FMUL_SInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    float32_t Rs1Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs1);
    float32_t Rs2Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs2);
    softfloat_roundingMode = RiscvToSoftfloatRm(Params.Rm);
    float32_t Result = f32_mul(Rs1Val, Rs2Val);
    WriteFloatReg(TargetExecutor.getRegisterFile(), Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

FDIV_SInstruction::FDIV_SInstruction() : FloatTypeRoundingInstruction(static_cast<uint32_t>(Opcodes::OP_FP), 0x3) {}

void FDIV_SInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    float32_t Rs1Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs1);
    float32_t Rs2Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs2);
    softfloat_roundingMode = RiscvToSoftfloatRm(Params.Rm);
    float32_t Result = f32_div(Rs1Val, Rs2Val);
    WriteFloatReg(TargetExecutor.getRegisterFile(), Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

FSQRT_SInstruction::FSQRT_SInstruction() : FloatTypeRoundingInstruction(static_cast<uint32_t>(Opcodes::OP_FP), 0xB) {}

void FSQRT_SInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    float32_t Rs1Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs1);
    softfloat_roundingMode = RiscvToSoftfloatRm(Params.Rm);
    float32_t Result = f32_sqrt(Rs1Val);
    WriteFloatReg(TargetExecutor.getRegisterFile(), Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

FSGNJ_SInstruction::FSGNJ_SInstruction() : FloatTypeNoRoundingInstruction(static_cast<uint32_t>(Opcodes::OP_FP), 0x0, 0x4) {}

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

FSGNJN_SInstruction::FSGNJN_SInstruction() : FloatTypeNoRoundingInstruction(static_cast<uint32_t>(Opcodes::OP_FP), 0x1, 0x4) {}

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

FSGNJX_SInstruction::FSGNJX_SInstruction() : FloatTypeNoRoundingInstruction(static_cast<uint32_t>(Opcodes::OP_FP), 0x2, 0x4) {}

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

FMIN_SInstruction::FMIN_SInstruction() : FloatTypeNoRoundingInstruction(static_cast<uint32_t>(Opcodes::OP_FP), 0x0, 0x5) {}

void FMIN_SInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    float32_t Rs1Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs1);
    float32_t Rs2Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs2);
    float Val1 = 0;
    std::memcpy(&Val1, &Rs1Val, sizeof(float));
    float Val2 = 0;
    std::memcpy(&Val2, &Rs2Val, sizeof(float));
    float Result = std::fmin(Val1, Val2);
    float32_t ResultBits = {};
    std::memcpy(&ResultBits, &Result, sizeof(float32_t));
    WriteFloatReg(TargetExecutor.getRegisterFile(), Params.Rd, ResultBits);
    TargetExecutor.getPC() += 4;
}

FMAX_SInstruction::FMAX_SInstruction() : FloatTypeNoRoundingInstruction(static_cast<uint32_t>(Opcodes::OP_FP), 0x1, 0x5) {}

void FMAX_SInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    float32_t Rs1Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs1);
    float32_t Rs2Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs2);
    float Val1 = 0;
    std::memcpy(&Val1, &Rs1Val, sizeof(float));
    float Val2 = 0;
    std::memcpy(&Val2, &Rs2Val, sizeof(float));
    float Result = std::fmax(Val1, Val2);
    float32_t ResultBits = {};
    std::memcpy(&ResultBits, &Result, sizeof(float32_t));
    WriteFloatReg(TargetExecutor.getRegisterFile(), Params.Rd, ResultBits);
    TargetExecutor.getPC() += 4;
}

FCVT_I2FInstruction::FCVT_I2FInstruction() : FloatTypeRoundingInstruction(static_cast<uint32_t>(Opcodes::OP_FP), 0x1A) {}

void FCVT_I2FInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1);
    float32_t Result = {};
    softfloat_roundingMode = RiscvToSoftfloatRm(Params.Rm);
    int ConversionType = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs2);
    if (ConversionType == 0)
        Result = i32_to_f32(Rs1Val);
    else
        Result = ui32_to_f32(Rs1Val);
    WriteFloatReg(TargetExecutor.getRegisterFile(), Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

FCVT_F2IInstruction::FCVT_F2IInstruction() : FloatTypeRoundingInstruction(static_cast<uint32_t>(Opcodes::OP_FP), 0x18) {}

void FCVT_F2IInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    float32_t Rs1Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs1);
    uint32_t Result = {};
    int ConversionType = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs2);
    if (ConversionType == 0)
        Result = f32_to_i32(Rs1Val, RiscvToSoftfloatRm(Params.Rm), false);
    else
        Result = f32_to_ui32(Rs1Val, RiscvToSoftfloatRm(Params.Rm), false);
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

FMV_X_WInstruction::FMV_X_WInstruction() : FloatTypeNoRoundingInstruction(static_cast<uint32_t>(Opcodes::OP_FP), 0x0, 0x1C) {}

void FMV_X_WInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Bits = TargetExecutor.getRegisterFile().readRegister(RegistersType::FLOAT_REGS, Params.Rs1);
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, Rs1Bits);
    TargetExecutor.getPC() += 4;
}

FMV_W_XInstruction::FMV_W_XInstruction() : FloatTypeNoRoundingInstruction(static_cast<uint32_t>(Opcodes::OP_FP), 0x0, 0x1E) {}

void FMV_W_XInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Bits = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1);
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::FLOAT_REGS, Params.Rd, Rs1Bits);
    TargetExecutor.getPC() += 4;
}

FEQ_SInstruction::FEQ_SInstruction() : FloatTypeNoRoundingInstruction(static_cast<uint32_t>(Opcodes::OP_FP), 0x2, 0x14) {}

void FEQ_SInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    float32_t Rs1Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs1);
    float32_t Rs2Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs2);
    bool Result = f32_eq(Rs1Val, Rs2Val);
    uint32_t ResultBit = (Result == true) ? 1 : 0;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, ResultBit);
    TargetExecutor.getPC() += 4;
}

FLT_SInstruction::FLT_SInstruction() : FloatTypeNoRoundingInstruction(static_cast<uint32_t>(Opcodes::OP_FP), 0x1, 0x14) {}

void FLT_SInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    float32_t Rs1Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs1);
    float32_t Rs2Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs2);
    bool Result = f32_lt_quiet(Rs1Val, Rs2Val);
    uint32_t ResultBit = (Result == true) ? 1 : 0;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, ResultBit);
    TargetExecutor.getPC() += 4;
}

FLE_SInstruction::FLE_SInstruction() : FloatTypeNoRoundingInstruction(static_cast<uint32_t>(Opcodes::OP_FP), 0x0, 0x14) {}

void FLE_SInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    float32_t Rs1Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs1);
    float32_t Rs2Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs2);
    bool Result = f32_le_quiet(Rs1Val, Rs2Val);
    uint32_t ResultBit = (Result == true) ? 1 : 0;
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, ResultBit);
    TargetExecutor.getPC() += 4;
}

FCLASS_SInstruction::FCLASS_SInstruction() : FloatTypeNoRoundingInstruction(static_cast<uint32_t>(Opcodes::OP_FP), 0x1, 0x1C) {}

void FCLASS_SInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    float32_t Rs1Val = ReadFloatReg(TargetExecutor.getRegisterFile(), Params.Rs1);
    int32_t Result = 0;
    
    // doing this shit... ooof...
    union ui32_f32 uA;
    uint_fast32_t uiA = 0;

    uA.f = Rs1Val;
    uiA = uA.ui;

    uint_fast16_t infOrNaN = (expF32UI( uiA ) == 0xFF);
    uint_fast16_t subnormalOrZero = (expF32UI( uiA ) == 0);
    bool sign = signF32UI( uiA );
    bool fracZero = (fracF32UI( uiA ) == 0);
    bool isNaN = isNaNF32UI( uiA );
    bool isSNaN = softfloat_isSigNaNF32UI( uiA );

    if ( sign && infOrNaN && fracZero )          
        Result = 1 << 0;
    else if ( sign && !infOrNaN && !subnormalOrZero ) 
        Result = 1 << 1;
    else if ( sign && subnormalOrZero && !fracZero )  
        Result = 1 << 2;
    else if ( sign && subnormalOrZero && fracZero )   
        Result = 1 << 3;
    else if (!sign && infOrNaN && fracZero )          
        Result = 1 << 7;
    else if (!sign && !infOrNaN && !subnormalOrZero ) 
        Result = 1 << 6;
    else if (!sign && subnormalOrZero && !fracZero )  
        Result = 1 << 5;
    else if (!sign && subnormalOrZero && fracZero )   
        Result = 1 << 4;
    else if (isNaN &&  isSNaN )                       
        Result = 1 << 8;
    else                      
        Result = 1 << 9;
    
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

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
    addNewInstr(std::make_shared<FCVT_I2FInstruction>());
    addNewInstr(std::make_shared<FCVT_F2IInstruction>());
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
