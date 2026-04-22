#include <cassert>

#include "MathHelper.h"

namespace r1scoviy {

uint32_t ExtractBits(uint32_t Imm, int StartBit, int EndBit) {
   
    assert(StartBit <= EndBit);
    assert(EndBit <= 31);

    const int Width = EndBit - StartBit + 1;

    const uint32_t Mask = (Width == 32) ? 0xFFFFFFFFU : ((1U << Width) - 1);

    return (Imm >> StartBit) & Mask;
}

int32_t GetSignExtImm(uint32_t Imm, int SignBitPos) {

    assert(SignBitPos > 0 || SignBitPos < 31);

    int32_t Mask = (1 << SignBitPos);

    Imm = Imm & ((1 << (SignBitPos + 1)) - 1);

    return ((static_cast<int32_t>(Imm) ^ Mask) - Mask);
}

uint32_t GetNextAlignedImm(uint32_t Imm, uint32_t Alignment) {

    uint32_t Offset = Imm % Alignment;

    if (Offset == 0)
        return Imm;

    return Imm + Alignment - Offset;
}

} // namespace r1scoviy