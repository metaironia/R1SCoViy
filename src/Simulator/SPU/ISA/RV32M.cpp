#include <cstdint>
#include <limits>
#include <memory>

#include "Simulator/SPU/Executor/Executor.h"

#include "RV32M.h"

namespace r1scoviy {

MULInstruction::MULInstruction() : RTypeInstruction(0x33, 0x0, 0x01) {}

void MULInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int64_t Rs1Val = static_cast<int64_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1));
    int64_t Rs2Val = static_cast<int64_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs2));
    int32_t Result = static_cast<int32_t>(Rs1Val * Rs2Val);
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

MULHInstruction::MULHInstruction() : RTypeInstruction(0x33, 0x1, 0x01) {}

void MULHInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int64_t Rs1Val = static_cast<int64_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1));
    int64_t Rs2Val = static_cast<int64_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs2));
    int64_t Product = Rs1Val * Rs2Val;
    int32_t Result = static_cast<int32_t>(Product >> 32);
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

MULHSUInstruction::MULHSUInstruction() : RTypeInstruction(0x33, 0x2, 0x01) {}

void MULHSUInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int64_t Rs1Val = static_cast<int64_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1));
    uint64_t Rs2Val = static_cast<uint64_t>(static_cast<uint32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs2)));
    int64_t Product = Rs1Val * static_cast<int64_t>(Rs2Val);
    int32_t Result = static_cast<int32_t>(static_cast<uint64_t>(Product) >> 32);
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

MULHUInstruction::MULHUInstruction() : RTypeInstruction(0x33, 0x3, 0x01) {}

void MULHUInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint64_t Rs1Val = static_cast<uint64_t>(static_cast<uint32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1)));
    uint64_t Rs2Val = static_cast<uint64_t>(static_cast<uint32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs2)));
    uint64_t Product = Rs1Val * Rs2Val;
    uint32_t Result = static_cast<uint32_t>(Product >> 32);
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, static_cast<int32_t>(Result));
    TargetExecutor.getPC() += 4;
}

DIVInstruction::DIVInstruction() : RTypeInstruction(0x33, 0x4, 0x01) {}

void DIVInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1);
    int32_t Rs2Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs2);
    int32_t Result;

    if (Rs2Val == 0) {

        Result = -1;
    } 
    else if (Rs1Val == std::numeric_limits<int32_t>::min() && Rs2Val == -1) {

        Result = Rs1Val;
    }
    else {

        Result = Rs1Val / Rs2Val;
    }
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

DIVUInstruction::DIVUInstruction() : RTypeInstruction(0x33, 0x5, 0x01) {}

void DIVUInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = static_cast<uint32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1));
    uint32_t Rs2Val = static_cast<uint32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs2));
    uint32_t Result;

    if (Rs2Val == 0) {

        Result = 0xFFFFFFFFu;
    } 
    else {

        Result = Rs1Val / Rs2Val;
    }
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, static_cast<int32_t>(Result));
    TargetExecutor.getPC() += 4;
}

REMInstruction::REMInstruction() : RTypeInstruction(0x33, 0x6, 0x01) {}

void REMInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    int32_t Rs1Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1);
    int32_t Rs2Val = TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs2);
    int32_t Result;

    if (Rs2Val == 0) {

        Result = Rs1Val;
    }
    else if (Rs1Val == std::numeric_limits<int32_t>::min() && Rs2Val == -1) {

        Result = 0;
    }
    else {

        Result = Rs1Val % Rs2Val;
    }
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, Result);
    TargetExecutor.getPC() += 4;
}

REMUInstruction::REMUInstruction() : RTypeInstruction(0x33, 0x7, 0x01) {}

void REMUInstruction::executeInstr(ExecutorUnit &TargetExecutor) const {
    const auto &Params = TargetExecutor.getInstructionParams();
    uint32_t Rs1Val = static_cast<uint32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs1));
    uint32_t Rs2Val = static_cast<uint32_t>(TargetExecutor.getRegisterFile().readRegister(RegistersType::INTEGER_REGS, Params.Rs2));
    uint32_t Result;

    if (Rs2Val == 0) {

        Result = Rs1Val;
    }
    else {

        Result = Rs1Val % Rs2Val;
    }
    TargetExecutor.getRegisterFile().writeRegister(RegistersType::INTEGER_REGS, Params.Rd, static_cast<int32_t>(Result));
    TargetExecutor.getPC() += 4;
}

void RV32MExtension::registerInstructions() {
    registerRTypeInstructions();
}

void RV32MExtension::registerRTypeInstructions() {
    addNewInstr(std::make_shared<MULInstruction>());
    addNewInstr(std::make_shared<MULHInstruction>());
    addNewInstr(std::make_shared<MULHSUInstruction>());
    addNewInstr(std::make_shared<MULHUInstruction>());
    addNewInstr(std::make_shared<DIVInstruction>());
    addNewInstr(std::make_shared<DIVUInstruction>());
    addNewInstr(std::make_shared<REMInstruction>());
    addNewInstr(std::make_shared<REMUInstruction>());
}

} // namespace r1scoviy