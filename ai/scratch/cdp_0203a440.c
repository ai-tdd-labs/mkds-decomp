// PURPOSE: Computes the remainder of an unsigned 64-bit division.
typedef unsigned long long u64;

asm u64 HasTouchPressed(u64 dividend, u64 divisor)
{
    DCD 0xe3a0105c
    DCD 0xe0020190
    DCD 0xe59f1034
    DCD 0xe3a00001
    DCD 0xe19130b2
    DCD 0xe3a0c000
    DCD 0xe3530000
    DCD 0x1a000003
    DCD 0xe59f1020
    DCD 0xe19110b2
    DCD 0xe3510005
    DCD 0x31a0c000
    DCD 0xe35c0000
    DCD 0xe19130b2
    DCD 0xe3a0c000
    DCD 0xe3a0105c
    DCD 0xe12fff1e
    DCD 0xdata_02175674
    DCD 0xdata_02175680
}
