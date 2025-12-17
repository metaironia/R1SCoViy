#ifndef SRC_SIMULATOR_SPU_ISA_INSTRUCTIONREGISTRY_H
#define SRC_SIMULATOR_SPU_ISA_INSTRUCTIONREGISTRY_H

class InstructionRegistry {
private:
    std::unordered_map<InstrID, ITypeInstruction *> ITypeInstrs;
    std::unordered_map<InstrID, MemITypeInstruction *> MemITypeInstrs;
    std::unordered_map<InstrID, RTypeInstruction *> RTypeInstrs;
    std::unordered_map<InstrID, STypeInstruction *> STypeInstrs;
    std::unordered_map<InstrID, BTypeInstruction *> BTypeInstrs;
    std::unordered_map<InstrID, UTypeInstruction *> UTypeInstrs;
    std::unordered_map<InstrID, JTypeInstruction *> JTypeInstrs;
    std::unordered_map<InstrID, R4TypeInstruction *> R4TypeInstrs;

public:
    void registerInstrsFromExtension(Extension &CurrentExtension);
};

#endif