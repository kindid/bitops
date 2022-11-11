#include <gtest/gtest.h>

#include "bitops.h"
//#include <ostream>

#define DEBUG_ON
#include "here.h"
#include "bits.h"

// whole bunch of tests - tbh using node to run the
// compiler failure test is probably easier than trying to
// mangle this into C++

s32 riscv_div(s32 dividend, s32 divisor)
{
    if (divisor == 0) {
        return -1;
    } else {
        // X86 will INTO at this point - RISCV does not
        // SOOooo.. trap it
        if (divisor == -1 && dividend == -0x80000000) {
            return 0x80000000;
        } else {
            return dividend / divisor;
        }
    }
}

s32 riscv_rem(s32 dividend, s32 divisor)
{
    if (divisor == 0) {
        return dividend;
    } else {
        // X86 will INTO at this point - RISCV does not
        // SOOooo.. trap it
        if (divisor == -1 && dividend == -0x80000000) {
            return 0x00000000;
        } else {
            return dividend % divisor;
        }
    }
}

TEST(RISCV_divide_by_0, basic)
{
    here << "START";
    here << riscv_div(s32(0x80000000), -1);
    here << riscv_div(s32(0x80000000), 1);
    here << riscv_div(s32(0x80000000), 2);
    here << riscv_rem(s32(0x80000000), 0);
    here << riscv_rem(s32(0x80000000), -1);
    here << riscv_rem(s32(0x80000000), 0);
//    EXPECT_EQ(true, c == 111_b3);
}

TEST(bit_tests, basic)
{
    bits<7> a(0b0011100);
    // how does one test compiler failures?
    //bits<7> b(0011100_b7);
    auto b = 0011100_b7;

    auto c = b.extract<2,3>();

    // todo -
    EXPECT_EQ(true, c == 111_b3);

    {
        auto a = 011_b3;
        auto b = a.sext<12>();
        EXPECT_EQ(b, 000000000011_b12);
    }

    {
        auto a = 011_b3;
        auto b = a.sext<12>();
        EXPECT_EQ(b, 000000000011_b12);
    }

    {
        auto a = 011_b3;
        // could extend and shift
        auto b = a.shl<1>();
        here << b;
//        EXPECT_EQ(b, 000000000011_b12);
    }

    {
        EXPECT_EQ((                            111_b3).sext<12>(),
                                      111111111111_b12);

        EXPECT_EQ((                            111_b3).sext<11>(),
                                       11111111111_b11);

        EXPECT_EQ((                       11111111_b8).sext<16>(),
                                  1111111111111111_b16);

        EXPECT_EQ((                       01111111_b8).sext<16>(),
                                  0000000001111111_b16);

        EXPECT_EQ((                       01111110_b8).sext<16>(),
                                  0000000011111110_b16);

        EXPECT_EQ((               1111111111111111_b16).sext<32>(),
                  11111111111111111111111111111111_b32);

        EXPECT_EQ((               1111111111111110_b16).sext<32>(),
                  11111111111111111111111111111110_b32);

        EXPECT_EQ((               0111111111111111_b16).sext<32>(),
                  00000000000000000011111111111111_b32);

        EXPECT_EQ((               0111111111111110_b16).sext<32>(),
                  00000000000000000111111111111110_b32);
    }
    {
        // if you want this converted to a primitive type you'll want to know if you want it signed or unsigned
        auto a = 111_b3;
        auto b = a.sext<12>();
        here << a;
        here << b;

        // issue - conversion to *signed* C type - figure it
        //EXPECT_EQ(b.primitive(), -4059);
    }

    {
        // if you want this converted to a primitive type you'll want to know if you want it signed or unsigned
//        auto a = 111_b3;
//        auto b = a.sext<12>();
//        here << a;
//        here << b;

        // quite crazy - a dot actually *is* part of the
        // udl literal suffix. however, this does mean fp24.8 is valid which is kinda
        // nice - but then fp24_8 is just as good and less confusing
        EXPECT_EQ(111_b3, 000_b3);//.ones());

        (0000_b4).twos();
        // issue - conversion to *signed* C type - figure it
        //EXPECT_EQ(b.primitive(), -4059);
    }

//    EXPECT_EQ(c, 111_b3);

//    here << c;

    // you can see this is *all* compilee time





    //bits<7> c(0011100_b7);

//    EXPECT_EQ(true,false);
}

#if 0
#define DEBUG_ON
#include "here.h"

template<unsigned B>
    using bit_prim_store =
        typename std::conditional<B <= 8, u8,
            typename std::conditional<B <= 16, u16,
                typename std::conditional<B <= 32, u32,
                    typename std::conditional<B <= 64, u64, void>
                    ::type>
                ::type>
            ::type>
        ::type;

template<unsigned B> struct bits {
    using bps_t = bit_prim_store<B>;
    constexpr static bps_t mask = (1U << B) - 1;
    constexpr explicit bits(bps_t _) : bps(_) {}

    bits operator -() const {
        return bits<B>(-bps);
    }

    // dude - dynamic vs static - how
//    sign_extend()

    // todo - signed vs unsigned comparisons...
    // do i even need it yet? *no*
    // 1111 < 0000 (signed)     -1 < 0
    // 1111 > 0000 (unsigned)   15 > 0
    // or return bits<1> - this would be very cool - bits<1> could add in a coerce to bool (and a bool constructor)
    bool operator ==(bits & b) { return bps == b.bps; }
    bool operator !=(bits & b) { return bps != b.bps; }

    // I'd like a massive case statement...

    // also... and, or, xor, nand and other (must be band etc because C++ sucks)
    // shift left, arithmetic shift left

    // ASL
    // 0001     0011        1->3
    // 0010     0100        2->4
    // 0011     0111        7->3
    // 0101     1011        5->11
    // 1000     0000        8->0
    // 1001     0011        9->3
    // 1111     1111        -1 -> -1
    // 1110     1100        -2 -> -4
    // 1101     1011        -3 -> -5

    // sra
    // srl
    // sla  - probably a waste of time
    // sll

    template<unsigned D>
    bits<D> zext() {
        return bits<D>(bit_prim_store<D>(bps));
    }

    template<unsigned D>
    bits<D> sext() {
        return bits<D>((bit_prim_store<D>(bps ^ (1u << (B - 1))) - (1u << (B - 1))));
    }

    bps_t bps;
};

template<unsigned B>
std::string binary_string(const bits<B> & b) {
    std::string q(B, '0');
    for (unsigned i = 0; i < B; i++) {
        // add mask/shift to bits and be happy
        // TBH - just get the bit (as 0/1) and - in x13 - that's all you need to do(!)
        if (b.bps & (1u << ((B - i) - 1))) {
            q[i] = '1';
        }
    }
    return q;
}

template<unsigned B>
    std::ostream & operator << (std::ostream & o, bits<B> d) {
        o << binary_string(d) << "_b" << B;
        return o;
    }

constexpr bool is_bin_char(char c) { return c == '0' || c == '1'; }

template <unsigned V> constexpr unsigned parse_binary_literal() { return V; }

template <unsigned V, char H, char...T>
constexpr unsigned parse_binary_literal()
{
    static_assert(is_bin_char(H), "only 0s and 1s allowed");
    return parse_binary_literal<((V << 1) | (H - '0')), T...>(); // (C)
}

#define BITS_B_UDL_(B) \
    template <char... STR> constexpr bits<B> operator"" _b ##B() { \
        static_assert(sizeof...(STR) == B, "Must have " #B " bits"); \
        return bits<B>(parse_binary_literal<0, STR...>()); \
    }

#define BMC_BMC(X) BITS_B_UDL_(X)
#include "bit_macro_counts.h"

TEST(Bitops_Basic, Test1) {
#if 0
    EXPECT_EQ(sizeof(bits<1>), 8 / 8);
    EXPECT_EQ(sizeof(bits<8>), 8 / 8);
    EXPECT_EQ(sizeof(bits<9>), 16 / 8);
    EXPECT_EQ(sizeof(bits<16>), 16 / 8);
    EXPECT_EQ(sizeof(bits<17>), 32 / 8);
    EXPECT_EQ(sizeof(bits<31>), 32 / 8);
    EXPECT_EQ(sizeof(bits<32>), 32 / 8);
    EXPECT_EQ(sizeof(bits<33>), 64 / 8);
    EXPECT_EQ(sizeof(bits<63>), 64 / 8);
#endif
//    auto c = 0b01100100;
//    auto b = 01100100_b;
    // signed - i *think* what's actually happening here is the that 'sign' operator
    // is part of the C lang and not the literal
    /// invalid argument type 'bits<7>' to unary expression
    //auto d = -1100100_b7;
    auto d = 1100100_b7;
    here << d;
//    EXPECT_EQ(c,b);
    here << -0b1;       // negatives *do* work - but not on a user defined literal


    // so here's the thing - i actually want to write chunks of code - run them through the compiler and see what fails
    // I'll be honest - id'
    auto b4_tst_0 = 1010_b4;
    //auto b3_tst = 101_b4;
    auto b4_tst_1 = 0101_b4;

    // you can't compare bits<X> and bits<Y> where X != Y because the
    // contents of the remaining bits is ambiguous

    // this is sort of ok but what it will require bit<7> to be defined *but* it's
    // a template - hmmm
    here << b4_tst_1.zext<7>();
    here << b4_tst_1.sext<7>();
    here << b4_tst_0.sext<7>();

//    here << binaryString(b3_tst);
//    here << typeid(b3_tst).name();

    // convert from b3 to b7 - use sign extension


    //decltype(010_b3);
//    here << FIRST;
//    here << SECOND;
//    here << THIRD;
    // the last one is "untestable" unless we configure gtest to call the compiler(!)
}
#endif
