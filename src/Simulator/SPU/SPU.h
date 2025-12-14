#ifndef SRC_SIMULATOR_SPU_SPU_H
#define SRC_SIMULATOR_SPU_SPU_H

class SPU {
private:
    uint32_t CurrentInstructionAddress;

    FetcherUnit Fetcher;
    DecoderUnit Decoder;
    ExecutorUnit Executor;
    
public:
    SPU(std::unique_ptr<RAMControllerUnit> &&RAMControllerModule);

    SPU(const &SPU Other);
    SPU &operator=(const &SPU Other);

    ~SPU();

    void start(uint32_t StartInstructionAddress);
}

#endif