#include <gtest/gtest.h>

#define DEBUG_ON
#include "here.h"
#include "bits.h"

// compilation failure test - will probably require string and ostream
// that's probably it
TEST(BitCtor, Constructor) {
    EXPECT_EQ(bits<1>(false), false);
    EXPECT_EQ(bits<1>(true), true);
    EXPECT_EQ(bits<8>(false), 00000000_b8);
    EXPECT_EQ(bits<8>(true), 11111111_b8);
    EXPECT_EQ(bits<8>(), 00000000_b8);
    EXPECT_EQ(bits<8>(), 00000000_b8);
}

TEST(BitCtor, SignExtension) {
    // you *have* to wrap this in parenthesis
    auto a = (1111_b4).sign_extend<7>();
//    EXPECT_EQ(1111_b4.sign_extend<7>(), 1111111_b7);
//    EXPECT_EQ(1000_b4.sign_extend<7>(), 1111000_b7);
//    EXPECT_EQ(0111_b4.sign_extend<9>(), 000000111_b9);
//    EXPECT_EQ(0001_b4.sign_extend<6>(), 000001_b7);
}


TEST(BitCtor, Printing) {
    // maybe i should prepend the count - it saves me hassle and is common between code and output
    here << to_string(0101101_b7);
    here << to_string(0101101_b7);
    here << to_string(010110111001_b12);

}
