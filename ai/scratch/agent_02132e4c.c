// PURPOSE: Computes the remainder of an unsigned 64-bit division.
typedef unsigned long long u64;

asm u64 _ull_mod(u64 dividend, u64 divisor)
{
    DCD 0xe92d58f0
    DCD 0xe3a04001
    DCD 0xe1935002
    DCD 0x1a000001
    DCD 0xe8bd58f0
    DCD 0xe12fff1e
    DCD 0xe1915003
    DCD 0x1a000027
    DCD 0xe1a01002
    DCD 0xeb000101
    DCD 0xe3540000
    DCD 0x11a00001
    DCD 0xe3a01000
    DCD 0xe8bd58f0
    DCD 0xe12fff1e
    DCD 0xe92d58f0
    DCD 0xe1a04001
    DCD 0xe3844001
    DCD 0xea000003
}
