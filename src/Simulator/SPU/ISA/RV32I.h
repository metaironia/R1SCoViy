#ifndef SRC_SIMULATOR_SPU_ISA_RV32I_H
#define SRC_SIMULATOR_SPU_ISA_RV32I_H

#include "InstructionTypes.h"
#include "Extension.h"

namespace r1scoviy {

// Forward declarations for RV32I instructions
class ADDInstruction;
class SUBInstruction;
class SLLInstruction;
class SLTInstruction;
class SLTUInstruction;
class XORInstruction;
class SRLInstruction;
class SRAInstruction;
class ORInstruction;
class ANDInstruction;

class ADDIInstruction;
class SLTIInstruction;
class SLTIUInstruction;
class XORIInstruction;
class ORIInstruction;
class ANDIInstruction;
class SLLIInstruction;
class SRLIInstruction;
class SRAIInstruction;
class LBInstruction;
class LHInstruction;
class LWInstruction;
class LBUInstruction;
class LHUInstruction;
class JALRInstruction;

class SBInstruction;
class SHInstruction;
class SWInstruction;

class BEQInstruction;
class BNEInstruction;
class BLTInstruction;
class BGEInstruction;
class BLTUInstruction;
class BGEUInstruction;

class LUIInstruction;
class AUIPCInstruction;

class JALInstruction;

class ECALLInstruction;

// RV32I Extension class
class RV32IExtension : public Extension {
public:
    RV32IExtension() = default;
    ~RV32IExtension() = default;
    
    const std::string_view getName() const override { return "RV32I"; };
    
    void registerInstructions() override;
    
private:
    void registerRTypeInstructions();
    void registerITypeInstructions();
    void registerSTypeInstructions();
    void registerBTypeInstructions();
    void registerUTypeInstructions();
    void registerJTypeInstructions();
};

// R-Type Instructions
class ADDInstruction : public RTypeInstruction {
public:
    ADDInstruction();
    ~ADDInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class SUBInstruction : public RTypeInstruction {
public:
    SUBInstruction();
    ~SUBInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class SLLInstruction : public RTypeInstruction {
public:
    SLLInstruction();
    ~SLLInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class SLTInstruction : public RTypeInstruction {
public:
    SLTInstruction();
    ~SLTInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class SLTUInstruction : public RTypeInstruction {
public:
    SLTUInstruction();
    ~SLTUInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class XORInstruction : public RTypeInstruction {
public:
    XORInstruction();
    ~XORInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class SRLInstruction : public RTypeInstruction {
public:
    SRLInstruction();
    ~SRLInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class SRAInstruction : public RTypeInstruction {
public:
    SRAInstruction();
    ~SRAInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class ORInstruction : public RTypeInstruction {
public:
    ORInstruction();
    ~ORInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class ANDInstruction : public RTypeInstruction {
public:
    ANDInstruction();
    ~ANDInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

// I-Type Instructions
class ADDIInstruction : public ITypeInstruction {
public:
    ADDIInstruction();
    ~ADDIInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class SLTIInstruction : public ITypeInstruction {
public:
    SLTIInstruction();
    ~SLTIInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class SLTIUInstruction : public ITypeInstruction {
public:
    SLTIUInstruction();
    ~SLTIUInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class XORIInstruction : public ITypeInstruction {
public:
    XORIInstruction();
    ~XORIInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class ORIInstruction : public ITypeInstruction {
public:
    ORIInstruction();
    ~ORIInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class ANDIInstruction : public ITypeInstruction {
public:
    ANDIInstruction();
    ~ANDIInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class SLLIInstruction : public BitwiseITypeInstruction {
public:
    SLLIInstruction();
    ~SLLIInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class SRLIInstruction : public BitwiseITypeInstruction {
public:
    SRLIInstruction();
    ~SRLIInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class SRAIInstruction : public BitwiseITypeInstruction {
public:
    SRAIInstruction();
    ~SRAIInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class LBInstruction : public ITypeInstruction {
public:
    LBInstruction();
    ~LBInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class LHInstruction : public ITypeInstruction {
public:
    LHInstruction();
    ~LHInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class LWInstruction : public ITypeInstruction {
public:
    LWInstruction();
    ~LWInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class LBUInstruction : public ITypeInstruction {
public:
    LBUInstruction();
    ~LBUInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class LHUInstruction : public ITypeInstruction {
public:
    LHUInstruction();
    ~LHUInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class JALRInstruction : public ITypeInstruction {
public:
    JALRInstruction();
    ~JALRInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

// S-Type Instructions
class SBInstruction : public STypeInstruction {
public:
    SBInstruction();
    ~SBInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class SHInstruction : public STypeInstruction {
public:
    SHInstruction();
    ~SHInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class SWInstruction : public STypeInstruction {
public:
    SWInstruction();
    ~SWInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

// B-Type Instructions
class BEQInstruction : public BTypeInstruction {
public:
    BEQInstruction();
    ~BEQInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class BNEInstruction : public BTypeInstruction {
public:
    BNEInstruction();
    ~BNEInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class BLTInstruction : public BTypeInstruction {
public:
    BLTInstruction();
    ~BLTInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class BGEInstruction : public BTypeInstruction {
public:
    BGEInstruction();
    ~BGEInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class BLTUInstruction : public BTypeInstruction {
public:
    BLTUInstruction();
    ~BLTUInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class BGEUInstruction : public BTypeInstruction {
public:
    BGEUInstruction();
    ~BGEUInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

// U-Type Instructions
class LUIInstruction : public UTypeInstruction {
public:
    LUIInstruction();
    ~LUIInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class AUIPCInstruction : public UTypeInstruction {
public:
    AUIPCInstruction();
    ~AUIPCInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

// J-Type Instructions
class JALInstruction : public JTypeInstruction {
public:
    JALInstruction();
    ~JALInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class ECALLInstruction : public ITypeInstruction {
public:
    ECALLInstruction();
    ~ECALLInstruction() = default;

    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

} // namespace r1scoviy

#endif // SRC_SIMULATOR_SPU_ISA_RV32I_H