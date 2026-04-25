#ifndef SRC_SIMULATOR_SPU_ISA_RV32F_H
#define SRC_SIMULATOR_SPU_ISA_RV32F_H

#include "InstructionTypes.h"
#include "Extension.h"
#include "Simulator/SPU/Executor/InstructionDispatcher.h"

namespace r1scoviy {

enum class RV32FRounding {
    RNE = 0, RTZ = 1, RDN = 2, RUP = 3, RMM = 4, DYN = 7
};

// Forward declarations for RV32F instructions
class FLWInstruction;
class FSWInstruction;

class FADD_SInstruction;
class FSUB_SInstruction;
class FMUL_SInstruction;
class FDIV_SInstruction;
class FSQRT_SInstruction;

class FSGNJ_SInstruction;
class FSGNJN_SInstruction;
class FSGNJX_SInstruction;

class FMIN_SInstruction;
class FMAX_SInstruction;

class FCVT_W_SInstruction;
class FCVT_WU_SInstruction;
class FCVT_S_WInstruction;
class FCVT_S_WUInstruction;

class FMV_X_WInstruction;
class FMV_W_XInstruction;

class FEQ_SInstruction;
class FLT_SInstruction;
class FLE_SInstruction;

class FCLASS_SInstruction;

class RV32FExtension : public Extension {
public:
    RV32FExtension() = default;
    ~RV32FExtension() = default;
    
    const std::string_view getName() const override { return "RV32F"; };
    
    void registerInstructions() override;
    
private:
    void registerLoadStoreInstructions();
    void registerArithmeticInstructions();
    void registerConversionInstructions();
    void registerComparisonInstructions();
};

class FLWInstruction : public ITypeInstruction {
public:
    FLWInstruction();
    ~FLWInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class FSWInstruction : public STypeInstruction {
public:
    FSWInstruction();
    ~FSWInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class FADD_SInstruction : public FloatTypeInstruction {
public:
    FADD_SInstruction();
    ~FADD_SInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class FSUB_SInstruction : public FloatTypeInstruction {
public:
    FSUB_SInstruction();
    ~FSUB_SInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class FMUL_SInstruction : public FloatTypeInstruction {
public:
    FMUL_SInstruction();
    ~FMUL_SInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class FDIV_SInstruction : public FloatTypeInstruction {
public:
    FDIV_SInstruction();
    ~FDIV_SInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class FSQRT_SInstruction : public FloatTypeInstruction {
public:
    FSQRT_SInstruction();
    ~FSQRT_SInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class FSGNJ_SInstruction : public RTypeInstruction {
public:
    FSGNJ_SInstruction();
    ~FSGNJ_SInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class FSGNJN_SInstruction : public RTypeInstruction {
public:
    FSGNJN_SInstruction();
    ~FSGNJN_SInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class FSGNJX_SInstruction : public RTypeInstruction {
public:
    FSGNJX_SInstruction();
    ~FSGNJX_SInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class FMIN_SInstruction : public RTypeInstruction {
public:
    FMIN_SInstruction();
    ~FMIN_SInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class FMAX_SInstruction : public RTypeInstruction {
public:
    FMAX_SInstruction();
    ~FMAX_SInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

// Conversion Instructions
class FCVT_I2FInstruction : public FloatTypeInstruction {
public:
    FCVT_I2FInstruction();
    ~FCVT_I2FInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class FCVT_F2IInstruction : public FloatTypeInstruction {
public:
    FCVT_F2IInstruction();
    ~FCVT_F2IInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class FMV_X_WInstruction : public RTypeInstruction {
public:
    FMV_X_WInstruction();
    ~FMV_X_WInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class FMV_W_XInstruction : public RTypeInstruction {
public:
    FMV_W_XInstruction();
    ~FMV_W_XInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

// Comparison Instructions
class FEQ_SInstruction : public RTypeInstruction {
public:
    FEQ_SInstruction();
    ~FEQ_SInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class FLT_SInstruction : public RTypeInstruction {
public:
    FLT_SInstruction();
    ~FLT_SInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class FLE_SInstruction : public RTypeInstruction {
public:
    FLE_SInstruction();
    ~FLE_SInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class FCLASS_SInstruction : public RTypeInstruction {
public:
    FCLASS_SInstruction();
    ~FCLASS_SInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

} // namespace r1scoviy

#endif // SRC_SIMULATOR_SPU_ISA_RV32F_H
