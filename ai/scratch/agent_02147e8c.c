// PURPOSE: Returns the fixed-point square root using the DS hardware unit.
// Positive 20.12 fixed-point inputs are submitted to the square-root coprocessor.
// Zero and negative inputs return zero without touching the hardware.

typedef signed int fx32;
typedef signed long long fx64;
typedef unsigned short u16;
typedef unsigned long long u64;

#define reg_CP_SQRTCNT (*(volatile u16 *)0x040002b0)
#define reg_CP_SQRT_PARAM (*(volatile u64 *)0x040002b8)

extern fx32 FX_GetSqrtResult(void);

fx32 FX_Sqrt(fx32 x)
{
    if (x > 0) {
        reg_CP_SQRTCNT = 1;
        reg_CP_SQRT_PARAM = (u64)((fx64)x << 32);
        return FX_GetSqrtResult();
    } else {
        return 0;
    }
}
