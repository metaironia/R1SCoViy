#ifndef SRC_SIMULATOR_SPU_ISA_EXTENSION_H
#define SRC_SIMULATOR_SPU_ISA_EXTENSION_H

class Extension {
private:
    using InstructionPtrVariant = std::variant<std::unique_ptr<IType>,
                                               std::unique_ptr<MemIType>,
                                               std::unique_ptr<Rtype>,
                                               std::unique_ptr<SType>,
                                               std::unique_ptr<BType>,
                                               std::unique_ptr<UType>,
                                               std::unique_ptr<JType>, 
                                               std::unique_ptr<R4Type>>;

    std::vector<InstructionPtrVariant> ExtensionRelatedInstrs;

public:
    virtual const std::string_view getName() = 0;

protected:
    Extension() = default;
    
    virtual ~Extension() = default;

    void addNewInstr(std::unique_ptr<Instruction> NewInstruction);
}

#endif