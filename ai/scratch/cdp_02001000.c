// PURPOSE: Computes the remainder of an unsigned 64-bit division.
typedef unsigned long long u64;

asm u64 func_02001000(u64 dividend, u64 divisor)
{
    DCD 0xe92d4010
    DCD 0xe59f003c
    DCD 0xe5900000
    DCD 0xe5d0408a
    DCD 0xeb013cbc
    DCD 0x08bd4010
    DCD 0x012fff1e
    DCD 0xe5d01087
    DCD 0xe1a02004
    DCD 0xe3a00007
    DCD 0xeb013cbc
    DCD 0xe3500000
    DCD 0x08bd4010
    DCD 0xeb013cbc
    DCD 0x08bd4010
    DCD 0xe92d4010
    DCD 0xe8bd4010
    DCD 0xe12fff1e
    DCD 0xdata_0217aa00
}
