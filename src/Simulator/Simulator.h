#ifndef SRC_SIMULATOR_SIMULATOR_H
#define SRC_SIMULATOR_SIMULATOR_H

#include <string_view>

#include <elfio/elfio.hpp>

#include "Simulator/Memory/Memory.h"
#include "Simulator/SPU/SPU.h"

namespace r1scoviy {

const uint32_t CmdArgvVirtualAddress = 0xC0000000; // 3 gb

const uint32_t StackVirtualAddress = 0xBFFFFFE0;

class Simulator {
private:
    RAMControllerUnit RAMController;
    SPU Processor;

public:
    Simulator(ExtensionRegistry &ExtensionRegistry)
        : RAMController(), Processor(ExtensionRegistry, RAMController) {}

    ~Simulator() = default;

    void start(int Argc, const char *Argv[]);

private:
    bool loadFile(ELFIO::elfio &Reader, const std::string_view Filepath);

    void initCmdArgs(int Argc, const char *Argv[]);

    void initSegments(const ELFIO::elfio &Reader);

    void initRAM(const ELFIO::elfio &Reader, int Argc, const char *Argv[]);
};

} // namespace r1scoviy

#endif