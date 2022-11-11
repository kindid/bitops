# Kindids C++, Templated, Compile Time Safe, Bit Operations Library

## Introduction

Before using this library please carefully consider what it is you require. This library was carefully constructed to provide as much compile time checking as possible for our RISC-V emulator project https://github.com/kindid/riscv-emu

* Bit fields of 1 to 64 bits can be stored and storage is optimized to the nearest power of 2 primitive type
* User defined literals are available that are a *precise* size.
    * The UDL literal suffix defines the bit field length. This is checked at compile time
* Comparison between the same size bit string is possible but not 
* Bit fields can be extract from inside others but this is *not* a dynamic process. The start and length of the extracted fields must be constexpr and are checked 
* Bit fields can be converted to/from C++ primitive types and the internal type is discoverable so that `decltype` can be used


Challenges
    Implementation of compiler failure tests
    Implementation of negatives
        negative requires an overide of the unary negation op
    Undefined behaviour
        shifts, signed shits, shifts where op > bit_width
    Characters that can exist in UDLs can be problematic e.g.
        1111_b4.sign_extend<4>()
    is *not* valid
        (1111_b4).sign_extend<4>()
    Only a single '.' can be used and it's use is *complex*
    Underscore can't be used as the number still has to parse as a numeric literal
    Negation is a double problem(!) and still gets false positives in compiler warnings because of the C preprocessor... -274 is actually "negate" "273" in the AST because the numeric literal could be expanded from a macro e.g. -EXPAND_THIS. Nasty!

## Examples

### Extracting fields from an MMU page table

```
{
    u32 fld = (u32 *) (get_TTBR0());
    if (fld.extract<0,2> == 00_b2) {
        // Ignore/fault
    }
    else if (fld.extract<0,2> == 01_b2) {
        // page table base address
    }
    else if (fld.extract<0,2> == 10_b2) {
        if (fld.extract<18,1>) {
            // Supersection
        } else {
            // Supersection Base Address
        }
    }
    else if (fld.extract<0,2> == 11_b2) {
        // reserved
    }
}
```

### Extracting fields from an instruction (RISCV)


```
lower 2 bits
then some other stuff;..
lots of //... ellide

```

### Literals

Forced size. Also allows _ as a separator (or will)
Can only be compared like for like
Supports - operator (TBH this is slightly flawed... 111_b3 is *not* -7 it's 0!!!. 001 -> 

### Bit extraction

```
// Pre-req
//////// ba9876543210
auto b = 110110110111_b12
```

- dude - a table of this would be pretty neat.

```
auto c = extract<0,3>();
ASSERT(c == 111_b3);
```

```
auto c = extract<2,5>();
ASSERT(c == 10110_b5);
```


### Comparisons

bit lengths must be the same

==
!=


### Zero Extension

// dude - is this a version of extract? seem wordy

### Sign Extension

(1111_b4).sign_extend<7>() ==   1111111_b7
(1000_b4).sign_extend<7>() ==   1111000_b7
0111_b4.sign_extend<9>() == 000000111_b9
0001_b4.sign_extend<6>() ==    000001_b7


100_b3.sign_extend<2>() ==    Compilation Failure



### Shifts

### Logical Operations









