////////////////////////////////////////////////////////////////////////////////
/// (C) 2012 kindid.co.uk
/// MIT licensed
////////////////////////////////////////////////////////////////////////////////

#include "here.h"

static constexpr char hex_chars[16]{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

std::string hex(u64 v, u32 width)
{
    std::string chars(width, '0');
    for (unsigned p = 0; p < width; p++) {
        chars[width - p - 1] = hex_chars[v & 0xf];
        v >>= 4;
    }
    return chars;
}

std::string hex(u32 v, u32 width)
{
    return hex(u64(v), width);
}

std::string hex(u16 v, u32 width)
{
    return hex(u64(v), width);
}

std::string hex(u8 v, u32 width)
{
    return hex(u64(v), width);
}

std::string hex(s8 v, u32 width)
{
    return hex(u8(v), width);
}

std::string hex(s16 v, u32 width)
{
    return hex(u16(v), width);
}

std::string hex(s32 v, u32 width)
{
    if (v < 0) {
        return "-" + hex(u32(-v), width);
    } else {
        return hex(u32(v), width);
    }
}

std::string hex(s64 v, u32 width)
{
    return hex(u64(v), width);
}
