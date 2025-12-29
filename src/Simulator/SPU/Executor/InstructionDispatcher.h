#ifndef SRC_SIMULATOR_SPU_EXECUTOR_INSTRUCTIONDISPATCHER_H 
#define SRC_SIMULATOR_SPU_EXECUTOR_INSTRUCTIONDISPATCHER_H 

#include "src/Simulator/SPU/ISA/InstructionTypes.h"

class InstructionDispatcher {
public:
    virtual InstructionID_t getInstrID(uint32_t Instr) const = 0;
    
protected:
    virtual ~InstructionDispatcher() = default;
    
    uint32_t extractBits(int StartBit, int EndBit) const;
};

class ITypeInstructionDispatcher: public InstructionDispatcher {
public:
    uint32_t getRs1Num() const { return extractBits(15, 19); }
    uint32_t getRdNum() const  { return extractBits(7, 11); }

protected:
    uint32_t getImm() const { return extractBits(20, 31); }

    uint32_t CraftSignExtImm(uint32_t Imm, int ImmSizeInBits) {
        
        int Mask = 1U << (ImmSizeInBits - 1);  

        return (Imm ^ Mask) - Mask;   
    }
};

class MemITypeInstructionDispatcher: public InstructionDispatcher {
protected:
    uint32_t getImm() const  { return extractBits(20, 31); }
    uint32_t getRs1Num() const { return extractBits(15, 19); }
    uint32_t getRdNum() const  { return extractBits(7, 11); }

    uint32_t getSignExtImm(uint32_t Imm);
};

class RTypeInstructionDispatcher: public InstructionDispatcher {
public:
    uint32_t getRs2Num() const { return extractBits(20, 24); }
    uint32_t getRs1Num() const { return extractBits(15, 19); }
    uint32_t getRdNum() const  { return extractBits(7, 11); }
};

class STypeInstructionDispatcher : public InstructionDispatcher {
public:
    uint32_t getRs1Num() const { return extractBits(15, 19); }
    uint32_t getRdNum() const  { return extractBits(7, 11); }

    uint32_t getMergedImm() const;
};

class BTypeInstructionDispatcher : public InstructionDispatcher {
public:
    uint32_t getRs2Num() const { return extractBits(20, 24); }
    uint32_t getRs1Num() const { return extractBits(15, 19); }

    uint32_t getMergedImm() const;

};

class UTypeInstructionDispatcher : public InstructionDispatcher {
public:
    uint32_t getImm() const { return extractBits(12, 31); }
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