#ifndef SRC_SIMULATOR_SPU_EXECUTOR_INSTRUCTIONDISPATCHER_H 
#define SRC_SIMULATOR_SPU_EXECUTOR_INSTRUCTIONDISPATCHER_H 

#include <cstdint>

class InstructionDispatcher {
public:
    virtual uint32_t getInstrID(uint32_t Instr) const = 0;
    
    uint32_t getOpcode() const { return extractBits(0, 6); }

protected:
    virtual ~InstructionDispatcher() = default;
    
    uint32_t extractBits(int StartBit, int EndBit) const;
};

class RTypeInstructionDispatcher: public InstructionDispatcher {
public:
    uint32_t getInstrID(uint32_t Instr) const override;

    uint32_t getRdNum()  const { return extractBits(7, 11); }
    uint32_t getFunct3() const { return extractBits(25, 31); }    
    uint32_t getRs1Num() const { return extractBits(15, 19); }
    uint32_t getRs2Num() const { return extractBits(20, 24); }
    uint32_t getFunct7() const { return extractBits(25, 31); }    
};

class ITypeInstructionDispatcher: public InstructionDispatcher {
public:
    uint32_t getInstrID(uint32_t Instr) const override;    

    uint32_t getRdNum()  const { return extractBits(7, 11); }
    uint32_t getFunct3() const { return extractBits(25, 31); }    
    uint32_t getRs1Num() const { return extractBits(15, 19); }
    uint32_t getImm()    const { return extractBits(20, 31); }

    // uint32_t CraftSignExtImm(uint32_t Imm, unsigned ImmSizeInBits) {
        
    //     uint32_t Mask = 1U << (ImmSizeInBits - 1);  

    //     return (Imm ^ Mask) - Mask;   
    // }
};

class STypeInstructionDispatcher : public InstructionDispatcher {
public:
    uint32_t getInstrID(uint32_t Instr) const override;    

    uint32_t getFunct3() const { return extractBits(25, 31); }
    uint32_t getRs2Num() const { return extractBits(20, 24); }   
    uint32_t getRs1Num() const { return extractBits(15, 19); }

    uint32_t getMergedImm() const;
};

class BTypeInstructionDispatcher : public InstructionDispatcher {
public:
    uint32_t getInstrID(uint32_t Instr) const override;    

    uint32_t getFunct3() const { return extractBits(25, 31); }
    uint32_t getRs2Num() const { return extractBits(20, 24); }   
    uint32_t getRs1Num() const { return extractBits(15, 19); }

    uint32_t getMergedImm() const;
};

class UTypeInstructionDispatcher : public InstructionDispatcher {
public:
    uint32_t getInstrID(uint32_t Instr) const override;

    uint32_t getImm()   const { return extractBits(12, 31); }
    uint32_t getRdNum() const { return extractBits(7, 11); }
};

class JTypeInstructionDispatcher : public InstructionDispatcher {
public:
    uint32_t getMergedImm() const;
    uint32_t getRdNum() const { return extractBits(7, 11); }
};

class R4TypeInstructionDispatcher : public InstructionDispatcher {
public:
    uint32_t getFs3Num() const { return extractBits(27, 31); }
    uint32_t getFs2Num() const { return extractBits(20, 24); }
    uint32_t getFs1Num() const { return extractBits(15, 19); }
    uint32_t getFdNum() const  { return extractBits(7, 11); }
};

#endif