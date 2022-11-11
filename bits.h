////////////////////////////////////////////////////////////////////////////////
/// (C) 2021 kindid.co.uk
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to
/// deal in the Software without restriction, including without limitation the
/// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
/// sell copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
/// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
/// IN THE SOFTWARE.
///
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "types.h"
//#include "here.h"
#include <string>

// bitops
// extract
// sign extend
// zero extend
// shifts
//  expanding
//  wrapping (rotate)
//  clipping (normal)
// rotates
// mask generation
// popcounts


template<bool B, class T, class F>
    struct bit_conditional {
        using type = F;
    };
template<class T, class F>
    struct bit_conditional<true, T, F> {
        using type = T;
    };

// todo; tbh this fits the bill right now - however, if >64bit store
// is needed the, maybe, use *really* long types (oft compiler specific)
// or use arrays of u8/u32 etc

// yeah - tbh this could be done different.
template<unsigned B>
    using bit_prim_store =
        typename bit_conditional<B <= 8, u8,
            typename bit_conditional<B <= 16, u16,
                typename bit_conditional<B <= 32, u32,
                    typename bit_conditional<B <= 64, u64, void>
                    ::type>
                ::type>
            ::type>
        ::type;

/// bits ///////////////////////////////////////////////////////////////////////

// signed and unsigned types please

template<unsigned B>
struct bits {
    // deduce minimal primitive type to store bits
    // optimizes size use
    using bps_t = bit_prim_store<B>;
    // "all bits set"
    // const or constexpr? doesn't matter
    // use constexpr plz
    const static bps_t mask = (1U << B) - 1;
    // just the top bit - used for sign extension
    const static bps_t top = 1U << (B - 1);
    //
    constexpr bits() : bps(0) { }
    constexpr explicit bits(bool _) : bps(_ ? mask : 0u) {
//            here << "fart " << _;
    }
    constexpr bits(const bits & _) : bps(_.bps) { }
    constexpr explicit bits(bps_t _) : bps(_) {}
    //
    bits operator -() const {
        return bits<B>((bps ^ top) - top);
    }

    constexpr operator bool() const { return any(); }

    constexpr bool any() const { return bps != 0u; }
    constexpr bool all() const { return bps == mask; }

    // < and > are not trivially supported as you cannot determine signed/unsigned tests
    // use the functionally equivalent
    constexpr bool operator ==(const bits & b) const { return bps == b.bps; }
    constexpr bool operator !=(const bits & b) const { return bps != b.bps; }

    bps_t primitive() const { return bps; }

    template<unsigned D>
        bits<D> zext() const {
            static_assert(D > B, "Output must have more bits than input");
            return bits<D>(bit_prim_store<D>(bps));
        }
    /*
        0001 -> 8 bits = 0000:0001
        1000 -> 8 bits = 1111:0000
        put it in the 8 bit type - invert bit 3 and subtract 8
        but then you must make sure that you clear all other bits

    */

    ///
    /// \brief sign_extend
    /// \return
    ///
    template<unsigned D>
    constexpr bits<D> sign_extend() const {
        static_assert(D > B, "Output must have more bits than input");
        using d_t = bit_prim_store<D>;
        return bits<D>(d_t((d_t(bps) ^ d_t(top)) - d_t(top)));
    }

    ///
    /// \brief zero_extend
    /// \return
    ///
    template<unsigned D>
    bits<D> zero_extend() const {
        static_assert(D > B, "Output must have more bits than input");
        return bits<D>(bit_prim_store<D>(bps));
    }

    ///
    /// \brief extract
    /// \return
    ///
    template<u8 S, u8 L>
    constexpr bits<L> extract() const {
        static_assert(L <= B, "Trying to extract more bits than exist");
        static_assert((S+L) <= B, "Not enough bits in input");
        return bits<L>((bps >> S) & ((1u << L) - 1));
    }

        // so there's "shift and clip"
        // and there's "shift and expand"
    template<unsigned D>
    constexpr bits shl() const {
        return bits((bps << D) & mask); }

    template<unsigned D>
    constexpr bits shr() const {
        return bits((bps >> D) & mask); }

    // todo is ~ operator
    constexpr bits ones() const {
    return bits(bps ^ mask); }

    // todo - is - operator
    constexpr bits twos() const {
    return bits((bps ^ top) - top); }

    constexpr bits band(bits _) const {
        return bits(_.bps & bps);
    }

    constexpr bits bor(bits _) const {
        return bits(_.bps | bps);
    }

    constexpr bits bxor(bits _) const {
        return bits(_.bps ^ bps);
    }

    void clean() { bps &= mask; }

    ///
    /// \brief bps - actual information storaged
    bps_t bps;
};

////////////////////////////////////////////////////////////////////////////////
// functional style
////////////////////////////////////////////////////////////////////////////////

template<unsigned B>
    bool eq(const bits<B> & x, const bits<B> & y) { return x == y; }
template<unsigned B>
    bool neq(const bits<B> & x, const bits<B> & y) { return x != y; }

// and/or/xor sign_extend etc

// todo - add the bX suffix please
// todo - "clamp" the writing of the B value
// atm '7' is displayed as '07' - either add logic
#if 0
template<unsigned B> std::string to_string(const bits<B> & b);

template<unsigned B>
    std::string to_string(const bits<(B < 10)> & b) {
        std::string q;  // todo; prefix?
        q.resize(B + 3);        // _bXX
        for (unsigned i = 0, cnt = B - 1; i < B; i++, cnt--) {
            q[i] = '0' + ((b & (1 << cnt)) & 1);
        }
        q[B] = '_';
        q[B + 1] = 'b';
        q[B + 2] = '0' + (B % 10);
        return q;
    }

template<unsigned B>
    std::string to_string(const bits<(B > 9)> & b) {
        std::string q;  // todo; prefix?
        q.resize(B + 4);        // _bXX
        for (unsigned i = 0, cnt = B - 1; i < B; i++, cnt--) {
            q[i] = '0' + ((b & (1 << cnt)) & 1);
        }
        q[B] = '_';
        q[B + 1] = 'b';
        q[B + 2] = '0' + (B / 10);
        q[B + 3] = '0' + (B % 10);
        return q;
    }
#endif

template<unsigned B>
    std::string to_string(const bits<B> & b) {
        std::string q;  // todo; prefix?
        q.resize(B + ((B < 10) ? 3 : 4));        // _bXX
        for (unsigned i = 0, cnt = B - 1; i < B; i++, cnt--) {
            q[i] = '0' + ((b & (1 << cnt)) & 1);
        }
        q[B] = '_';
        q[B + 1] = 'b';
        if constexpr (B < 10) {
            q[B + 2] = '0' + B;
        } else {
            q[B + 2] = '0' + (B / 10);
            q[B + 3] = '0' + (B % 10);
        }
        return q;
    }

template<unsigned B>
    std::ostream & operator << (std::ostream & o, bits<B> d) {
        o << to_string(d) << "_b" << B;
        return o;
    }

constexpr bool is_bin_char(char c) {
    return (c | 1) == '1';
}

template <unsigned V>
    constexpr unsigned parse_binary_literal() {
        return V; }

template <unsigned V, char H, char...T>
    constexpr unsigned parse_binary_literal()
    {
        static_assert(is_bin_char(H), "only 0s and 1s allowed");
        return parse_binary_literal<((V << 1) | (H & 1)), T...>(); // (C)
    }

#define BITS_B_UDL_(B) \
    template <char... STR> \
        constexpr bits<B> operator"" _b ##B() { \
            static_assert(sizeof...(STR) == B, "Must be exactly " #B " bits long"); \
            return bits<B>(bits<B>::bps_t(parse_binary_literal<0, STR...>())); \
        }

#include "bit_macro_counts.h"
BITS_COUNT_1_64_(BITS_B_UDL_)
#undef BITS_B_UDL_
#undef BITS_COUNT_1_64_
