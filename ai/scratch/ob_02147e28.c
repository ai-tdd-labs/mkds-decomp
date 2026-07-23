typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef signed int fx32;
typedef signed long long fx64;

#define reg_CP_DIVCNT       (*(volatile u16 *)0x04000280)
#define reg_CP_DIV_RESULT   (*(volatile u64 *)0x040002A0)

fx32 FX_GetDivResult(void)
{
    while (reg_CP_DIVCNT & 0x8000) {}
    return (fx32)((reg_CP_DIV_RESULT + (1 << (0x14 - 1))) >> 0x14);
}
