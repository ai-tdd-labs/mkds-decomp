// PURPOSE: Computes the remainder of an unsigned 64-bit division.
typedef unsigned long long u64;

asm u64 StructCY_SomeFn(u64 dividend, u64 divisor)
{
    DCD 0xe3a02000
    DCD 0xe1c020b0
    DCD 0xe1c020b2
    DCD 0xe1c020b4
    DCD 0xe1c020b6
    DCD 0xe1c020b8
    DCD 0xe1c020ba
    DCD 0xe1c020bc
    DCD 0xe3a01014
    DCD 0xe1c010be
    DCD 0xe3a01008
    DCD 0xe1c011b0
    DCD 0xe1c021b2
    DCD 0xe1c020b6
    DCD 0xe1c020b8
    DCD 0xe3a02000
    DCD 0xe5802020
    DCD 0xe5802024
    DCD 0xe12fff1e
}
