#ifndef SRC_MATHHELPER_H
#define SRC_MATHHELPER_H

#include <cstdint>

namespace r1scoviy {

uint32_t ExtractBits(uint32_t Instruction, int StartBit, int EndBit);

int32_t GetSignExtImm(uint32_t Imm, int SignBitPos);

} // namespace r1scoviy

#endif