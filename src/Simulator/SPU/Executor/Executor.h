#ifndef SRC_SIMULATOR_SPU_EXECUTOR_H
#define SRC_SIMULATOR_SPU_EXECUTOR_H

class ExecutorUnit {
private:
    RISCVISA ISA;

    std::shared_ptr<RAMControllerUnit> RAMController;
    RegisterFileUnit Registers;

    uint32_t CurrentInstr;

public:
    ExecutorUnit(std::shared_ptr<RAMControllerUnit> &&RAMControllerModule, RISCVISA TargetISA);

    void executeInstr(uint32_t Instr);

    uint32_t getCurrentInstr();
}

#endif