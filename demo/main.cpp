
#include "bits.h"

#define HERE_ON
#include "here.h"

int main(int argc, char *argv[])
{
    auto b = 0100_b4;
    here << b;
    return b;
}
