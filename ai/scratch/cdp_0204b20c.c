// PURPOSE: Computes the remainder of an unsigned 64-bit division.
typedef unsigned long long u64;

asm u64 FindTable0IndexForValue_from_thumb(u64 dividend, u64 divisor)
{
    DCD 0x2500b4f0
    DCD 0x4a0d43ec
    DCD 0x4b0d6812
    DCD 0x4b0d681e
    DCD 0x18f3681b
    DCD 0x4a0c18d3
    DCD 0x599600ae
    DCD 0x1c0718f6
    DCD 0x42b94077
    DCD 0x1c2cd101
    DCD 0x1c6de004
    DCD 0x0c2d042d
    DCD 0xd3f12d1d
    DCD 0x18f3681b
    DCD 0x4a0c18d3
    DCD 0x2500b4f0
    DCD 0xdata_021545d8
    DCD 0xdata_02154604
    DCD 0xdata_02154694
}
