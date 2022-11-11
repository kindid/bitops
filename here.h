////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <iostream>

#include "types.h"

// change to "hex"
// add "binary" (although this is also elsewhere)
std::string hex(u8 v, u32 width = 2);
std::string hex(u16 v, u32 width = 4);
std::string hex(u32 v, u32 width = 8);
std::string hex(u64 v, u32 width = 16);

std::string hex(s8 v, u32 width = 2);
std::string hex(s16 v, u32 width = 4);
std::string hex(s32 v, u32 width = 8);
std::string hex(s64 v, u32 width = 16);

//template<unsigned T> void binary(const bits<T> & b) {

//}

// you can define an ostream for each inclusion if you want

struct dbg_out_on : public std::ostream
{
    dbg_out_on()
        : std::ostream(std::cout.rdbuf())   // if you don't do this macOS/XCode STL
    {
        old_flags = std::cout.flags();
    }

    virtual ~dbg_out_on() override {
        std::cout << std::endl;
        std::cout.flags(old_flags);
    }

    template <typename T> const dbg_out_on &operator<<(const T &v) const {
        std::cout << v;
        return *this;
    }

    template <u8> const dbg_out_on &operator<<(const u8 &v) const {
        std::cout << (u32)(v);
        return *this;
    }

    std::ios_base::fmtflags old_flags;
};

struct dbg_out_off //: public std::ostream
{
    template <typename T>
        const dbg_out_off &operator<<(const T &v) const {
            return *this;
        }
};

// change to "here_on"
#ifdef DEBUG_ON
#define here dbg_out_on() << ("file://" __FILE__  ":") << __LINE__ << ": "
#define h_wrap(X) " " << #X << "=" << X
#else
#define here dbg_out_off() << __FILE__ << ":" << __LINE__ << ": "

#define h_wrap(X) " " << #X << "=" << X
#endif
