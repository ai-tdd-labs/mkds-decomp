typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef signed int fx32;
typedef signed long long fx64;

#define reg_CP_DIVCNT       (*(volatile u16 *)0x04000280)
#define reg_CP_DIV_NUMER    (*(volatile u64 *)0x04000290)
#define reg_CP_DIV_DENOM    (*(volatile u64 *)0x04000298)

void FX_InvAsync(fx32 x)
{
    reg_CP_DIVCNT = 0x1;
    reg_CP_DIV_NUMER = (u64)((fx64)0x00001000 << 32);
    reg_CP_DIV_DENOM = (u32)x;
}
