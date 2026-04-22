#ifndef SRC_MATHHELPER_H
#define SRC_MATHHELPER_H

#include <cstdint>

namespace r1scoviy {

uint32_t ExtractBits(uint32_t Instruction, int StartBit, int EndBit);

int32_t GetSignExtImm(uint32_t Imm, int SignBitPos);

uint32_t GetNextAlignedImm(uint32_t Imm, uint32_t Alignment);

} // namespace r1scoviy

#endif