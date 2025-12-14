#ifndef SRC_SIMULATOR_SPU_ISA_RV32I_H
#define SRC_SIMULATOR_SPU_ISA_RV32I_H

struct RV32IInfo {
    uint16_t getImm();
    uint8_t getRs1();
    uint8_t getFunct3();
    uint8_t getRd();
    uint8_t getOpcode();
    
}

#endif