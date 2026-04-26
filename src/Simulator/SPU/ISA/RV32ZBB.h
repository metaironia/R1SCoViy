#ifndef SRC_SIMULATOR_SPU_ISA_RV32ZBB_H
#define SRC_SIMULATOR_SPU_ISA_RV32ZBB_H

#include "InstructionTypes.h"
#include "Extension.h"

namespace r1scoviy {

class ANDNInstruction;
class ORNInstruction;
class XNORInstruction;
class MAXInstruction;
class MAXUInstruction;
class MINInstruction;
class MINUInstruction;
class ROLInstruction;
class RORInstruction;
class RORIInstruction;
class SEXTBInstruction;
class SEXTHInstruction;
class ZEXTBInstruction;
class ZEXTHInstruction;
class CLZInstruction;
class CTZInstruction;
class CPOPInstruction;
class ORC_BInstruction;
class REV8Instruction;

class RV32ZbbExtension : public Extension {
public:
    RV32ZbbExtension() = default;
    ~RV32ZbbExtension() = default;
    
    const std::string_view getName() const override { return "RV32Zbb"; };
    
    void registerInstructions() override;
    
private:
    void registerRTypeInstructions();
    void registerITypeInstructions();
};

class ANDNInstruction : public RTypeInstruction {
public:
    ANDNInstruction();
    ~ANDNInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class ORNInstruction : public RTypeInstruction {
public:
    ORNInstruction();
    ~ORNInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class XNORInstruction : public RTypeInstruction {
public:
    XNORInstruction();
    ~XNORInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class MAXInstruction : public RTypeInstruction {
public:
    MAXInstruction();
    ~MAXInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class MAXUInstruction : public RTypeInstruction {
public:
    MAXUInstruction();
    ~MAXUInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class MINInstruction : public RTypeInstruction {
public:
    MINInstruction();
    ~MINInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class MINUInstruction : public RTypeInstruction {
public:
    MINUInstruction();
    ~MINUInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class ROLInstruction : public RTypeInstruction {
public:
    ROLInstruction();
    ~ROLInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class RORInstruction : public RTypeInstruction {
public:
    RORInstruction();
    ~RORInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class SEXTBInstruction : public UltraBitwiseITypeInstruction {
public:
    SEXTBInstruction();
    ~SEXTBInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class SEXTHInstruction : public UltraBitwiseITypeInstruction {
public:
    SEXTHInstruction();
    ~SEXTHInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class ZEXTHInstruction : public RTypeInstruction {
public:
    ZEXTHInstruction();
    ~ZEXTHInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class CLZInstruction : public UltraBitwiseITypeInstruction {
public:
    CLZInstruction();
    ~CLZInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class CTZInstruction : public UltraBitwiseITypeInstruction {
public:
    CTZInstruction();
    ~CTZInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class CPOPInstruction : public UltraBitwiseITypeInstruction {
public:
    CPOPInstruction();
    ~CPOPInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class RORIInstruction : public BitwiseITypeInstruction {
public:
    RORIInstruction();
    ~RORIInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class ORC_BInstruction : public UltraBitwiseITypeInstruction {
public:
    ORC_BInstruction();
    ~ORC_BInstruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

class REV8Instruction : public UltraBitwiseITypeInstruction {
public:
    REV8Instruction();
    ~REV8Instruction() = default;
    
    void executeInstr(ExecutorUnit &TargetExecutor) const override;
};

} // namespace r1scoviy

#endif // SRC_SIMULATOR_SPU_ISA_RV32ZBB_H
