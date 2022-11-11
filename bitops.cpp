#include "bitops.h"
#if 0
constexpr u32 extract(u32 v, u32 first, u32 bits) {
    return (v >> first) & ((1u << bits) - 1);
}

u32 sign_extend(u8 x) {
    return s32((u32(x) ^ 0x80) - 0x80);
}

u32 sign_extend(u16 x) {
    return s32((u32(x) ^ 0x8000) - 0x8000);
}

u32 sign_extend(u32 x, u32 bit) {
    return s32((u32(x) ^ (1u << bit)) - (1u << bit));
}

// yeah, you get a 32 bit unsigned..
constexpr u32 signed_extract(u32 v, u32 first, u32 bits)
{
    // 4 = 1 << 5 = 1 10 100 1000 10000 100000 -1 = 011111
    // 1 << 4 = 10000 - 1= 01111
    // 1 << 1 = 10 - 1 = 1
    //
    // std::cout << std::endl;
    // std::cout << "kfb     = " << std::bitset<32>(v) << " " << first << " " << bits << std::endl;
    u32 extracted = extract(v, first, bits);
            //v >> first) & ((1u << bits) - 1);
    // std::cout << "extr0   = " << std::bitset<32>(extracted) << std::endl;
    // std::cout << "sexmask = " << std::bitset<32>((1U << (bits - 1))) << std::endl;

    if (extracted & (1U << (bits - 1)))
    {
        // std::cout << "mask    = " << std::bitset<32>(~0u << (bits)) << std::endl;
        extracted |= (~0u << (bits));
    }
    // std::cout << "extr1   = " << std::bitset<32>(extracted) << std::endl;
    return extracted;
    // is the top bit set?
}
#endif
