#ifndef SRC_SIMULATOR_SIMULATOR_H
#define SRC_SIMULATOR_SIMULATOR_H

#include <cstdint>
#include <memory>

#include "elfio/elfio.hpp"

#include "Simulator/Memory/Memory.h"
#include "Simulator/SPU/SPU.h"

namespace r1scoviy {

class Simulator {
private:
    RAMControllerUnit RAMController;
    SPU Processor;

public:
    Simulator(ExtensionRegistry &ExtensionRegistry)
        : RAMController(), Processor(ExtensionRegistry, RAMController) {}

    ~Simulator();

    bool loadFile(const std::string &Filepath);

private:
    void initRAM(const ELFIO::elfio &Reader);
};

} // namespace r1scoviy

#endif