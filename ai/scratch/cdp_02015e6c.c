// PURPOSE: Computes the remainder of an unsigned 64-bit division.
typedef unsigned long long u64;

asm u64 CreateAnimBlock_BVA(u64 dividend, u64 divisor)
{
    DCD 0xe59f3040
    DCD 0xe3a0c000
    DCD 0xe5933000
    DCD 0xe580300c
    DCD 0xe5d22017
    DCD 0xe5c02019
    DCD 0xe5801008
    DCD 0xe5d01019
    DCD 0xe3510000
    DCD 0x912fff1e
    DCD 0xe38c2c01
    DCD 0xe080108c
    DCD 0xe1c121ba
    DCD 0xe5d22017
    DCD 0xe5c02019
    DCD 0xe59f3040
    DCD 0x3afffff8
    DCD 0xe12fff1e
    DCD 0xdata_021617d4
}
