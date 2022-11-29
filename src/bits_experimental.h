#pragma once

#include "bits.h"

// this is, frankly, a little evil
// move this to "bits_experimental.h"

template<unsigned WZ>
    struct bit_container {
        // internal type is up to you...
        // i think this is actually an array of bits<32>...
        u32 data[(WZ + 31) >> 5];
    };

// this can *only* be placed *inside* a bit_container
// it has size 1 (which sucks BTW)
template<unsigned S, unsigned L>
    struct bit_field {
        static constexpr u32 mask = (1u << L) - 1;
        // you'd have to pass this in (or use macro shit)
    //    struct parent =
        bit_field & operator =(bits<L> i) {
            u32 * bc = (u32 *)(bc);
            // todo - bit fields split across words (possibly warn at compile time)
            bc[S >> 5] |= (u32(i.bps) << (S & 0x1f));
            return *this;
        }
        // todo - again "split"
        bits<L> operator*() {
            // can't do this because the length is runtime..
            //bit_container * bc = (bit_container *)(bc);
            //bits<32>()
            u32 * bc = (u32 *)(bc);
            // dynamic - you can't actually check that the bits are properly masked
            return bits<L>((bc[S >> 5] >> (S & 0x1f)) & mask);
    //        bc[S >> 5] |= (u32(i.bps) << (S & 0x1f));
        }
    };
