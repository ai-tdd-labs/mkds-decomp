// PURPOSE: Computes the remainder of an unsigned 64-bit division.
typedef unsigned long long u64;

asm u64 Fs_RomArchive_ReadFn_Default(u64 dividend, u64 divisor)
{
    DCD 0xe92d4000
    DCD 0xe24dd00c
    DCD 0xe59fc034
    DCD 0xe1a0e001
    DCD 0xe58dc000
    DCD 0xe58d0004
    DCD 0xe3a01001
    DCD 0xe59f0024
    DCD 0xe58d1008
    DCD 0xe1a01002
    DCD 0xe5900000
    DCD 0xe1a0200e
    DCD 0xeb05044f
    DCD 0xe58dc000
    DCD 0xe58d0004
    DCD 0xe92d4000
    DCD 0xe12fff1e
    DCD 0xUnkStructRelated_SaveFnPtr
    DCD 0xdata_0216f358
}
