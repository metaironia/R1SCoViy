#ifndef SRC_SIMULATOR_SPU_ISA_INSTRUCTIONTYPES_H
#define SRC_SIMULATOR_SPU_ISA_INSTRUCTIONTYPES_H

template <typename E>
class Extension {


}

class Instruction {
private:
    uint32_t Instr;

public:
    Instruction(uint32_t TargetInstr);

    extractBits(int StartBit, int EndBit);
};

class ITypeInstruction : public Instruction {
public:
    uint8_t getRs1Num() { return extractBits(15, 19); }
    uint8_t getRdNum()  { return extractBits(7, 11); }

    virtual void operator(Register_t &Rs1, Register_t &Rd) = 0;

private:
    uint16_t getImm()   { return extractBits(20, 31); }

    uint16_t CraftSignExtImm(uint32_t Imm, int ImmSizeInBits) {
        
        int Mask = 1U << (ImmSizeInBits - 1);  

        return (Imm ^ Mask) - Mask;   
    }
}

class MemITypeInstruction : public Instruction {
public:    
    uint16_t getImm()   { return extractBits(20, 31); }
    uint8_t getRs1Num() { return extractBits(15, 19); }
    uint8_t getRdNum()  { return extractBits(7, 11); }

    virtual void operator( Register_t &Rs1, Register_t &Rd,
                          std::shared_ptr<RAMControllerUnit> RAMController) = 0;

private:
    uint32_t getSignExtImm(uint16_t Imm);
}

class RTypeInstruction : public Instruction {
public:
    uint8_t getRs2Num() { return extractBits(20, 24); }
    uint8_t getRs1Num() { return extractBits(15, 19); }
    uint8_t getRdNum()  { return extractBits(7, 11); }

    virtual void operator(Register_t &Rs2, Register_t &Rs1, Register_t &Rd) = 0;
}

class STypeInstruction : public Instruction {
public:
    uint8_t getRs1Num() { return extractBits(15, 19); }
    uint8_t getRdNum()  { return extractBits(7, 11); }

    uint8_t getMergedImm();

    virtual void operator(Register_t &Rs2, Register_t &Rs1,
                          std::shared_ptr<RAMControllerUnit> RAMController) = 0;
}

class BTypeInstruction : public Instruction {
public:
    uint8_t getRs2Num() { return extractBits(20, 24); }
    uint8_t getRs1Num()  { return extractBits(15, 19); }

    uint8_t getMergedImm();

    virtual void operator(Register_t &Rs2, Register_t &Rs1) = 0;
}

class UTypeInstruction : public Instruction {
public:
    uint32_t getImm()  { return extractBits(12, 31); }
    uint8_t getRdNum() { return extractBits(7, 11); }

    virtual void operator(Register_t &Rd) = 0;
}

class JTypeInstruction : public Instruction {
public:
    uint32_t getMergedImm();
    uint8_t getRdNum() { return extractBits(7, 11); }

    virtual void operator(Register_t &Rd) = 0;
}

class R4TypeInstruction : public Instruction {
public:
    uint8_t getFs3Num() { return extractBits(27, 31); }
    uint8_t getFs2Num() { return extractBits(20, 24); }
    uint8_t getFs1Num() { return extractBits(15, 19); }
    uint8_t getFdNum() { return extractBits(7, 11); }

    virtual void operator(Register_t &Fs3, Register_t &Fs2,
                          Register_t &Fs1, Register_t &Fd) = 0;
}

#endif