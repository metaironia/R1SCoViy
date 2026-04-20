#ifndef SRC_SIMULATOR_SIMULATOR_H
#define SRC_SIMULATOR_SIMULATOR_H

#include <string_view>

#include <elfio/elfio.hpp>

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

    void start(const std::string_view Filepath);

private:
    bool loadFile(const std::string_view Filepath);

    void initRAM(const ELFIO::elfio &Reader);
};

} // namespace r1scoviy

#endif