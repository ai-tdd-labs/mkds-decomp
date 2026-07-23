// PURPOSE: Calculates the reciprocal of a fixed-point value.
// Starts the reciprocal hardware operation for x, then waits for it to finish.
// Returns the probably 64-bit result from the division hardware registers.

typedef int fx32;
typedef unsigned long long u64;

extern void FX_InvAsync(fx32 x);

u64 FX_Inv64(fx32 x)
{
    FX_InvAsync(x);

    while (*(volatile unsigned short *)0x04000280 & 0x8000) {
    }

    return *(volatile u64 *)0x040002a0;
}
