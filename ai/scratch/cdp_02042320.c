// PURPOSE: Computes the remainder of an unsigned 64-bit division.
typedef unsigned long long u64;

asm u64 CountAreaType4_from_thumb(u64 dividend, u64 divisor)
{
    DCD 0x2500b570
    DCD 0x4e0f1c2c
    DCD 0x1c016830
    DCD 0x88093178
    DCD 0xd9122900
    DCD 0xf0001c20
    DCD 0x3044f861
    DCD 0x28047800
    DCD 0x1c68d102
    DCD 0x0c050400
    DCD 0x04001c60
    DCD 0x68300c04
    DCD 0x31781c01
    DCD 0xd9122900
    DCD 0xf0001c20
    DCD 0x2500b570
    DCD 0x4718bc08
    DCD 0xdata_02175620
    DCD 0x00000102
}
