#ifndef SRC_SIMULATOR_SPU_ISA_RV32M_H
#define SRC_SIMULATOR_SPU_ISA_RV32M_H

#include "InstructionTypes.h"
#include "Extension.h"
#include "Simulator/SPU/Executor/InstructionDispatcher.h"

namespace r1scoviy {

class MULInstruction;
class MULHInstruction;
class MULHSUInstruction;
class MULHUInstruction;
class DIVInstruction;
class DIVUInstruction;
class REMInstruction;
class REMUInstruction;

class RV32MExtension : public Extension {
public:
    RV32MExtension() = default;
    ~RV32MExtension() = default;

    const std::string_view getName() const override { return "RV32M"; };

    void registerInstructions() override;

private:
    void registerRTypeInstructions();
};

class MULInstruction : public RTypeInstruction {
public:
    MULInstruction();
    ~MULInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class MULHInstruction : public RTypeInstruction {
public:
    MULHInstruction();
    ~MULHInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class MULHSUInstruction : public RTypeInstruction {
public:
    MULHSUInstruction();
    ~MULHSUInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class MULHUInstruction : public RTypeInstruction {
public:
    MULHUInstruction();
    ~MULHUInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class DIVInstruction : public RTypeInstruction {
public:
    DIVInstruction();
    ~DIVInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class DIVUInstruction : public RTypeInstruction {
public:
    DIVUInstruction();
    ~DIVUInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class REMInstruction : public RTypeInstruction {
public:
    REMInstruction();
    ~REMInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class REMUInstruction : public RTypeInstruction {
public:
    REMUInstruction();
    ~REMUInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

} // namespace r1scoviy

#endif // SRC_SIMULATOR_SPU_ISA_RV32M_H