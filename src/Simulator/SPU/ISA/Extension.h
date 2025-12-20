#ifndef SRC_SIMULATOR_SPU_ISA_EXTENSION_H
#define SRC_SIMULATOR_SPU_ISA_EXTENSION_H

class Extension {
private:
    using InstructionPtrVariant = std::variant<std::shared_ptr<IType>,
                                               std::shared_ptr<MemIType>,
                                               std::shared_ptr<Rtype>,
                                               std::shared_ptr<SType>,
                                               std::shared_ptr<BType>,
                                               std::shared_ptr<UType>,
                                               std::shared_ptr<JType>, 
                                               std::shared_ptr<R4Type>>;

    std::vector<InstructionPtrVariant> ExtensionRelatedInstrs;

public:
    virtual const std::string_view getName() = 0;

protected:
    Extension() = default;
    
    virtual ~Extension() = default;

    void addNewInstr(std::unique_ptr<Instruction> NewInstruction);
}

#endif