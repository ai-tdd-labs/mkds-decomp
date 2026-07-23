typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef long long fx64;
typedef int fx32;

void FX_DivAsync(fx32 numerator, fx32 denominator) {
    *(volatile u16 *)0x4000280 = 0x1;
    *(volatile u64 *)0x4000290 = (u64)((fx64)numerator << 32);
    *(volatile u64 *)0x4000298 = (u32)denominator;
}
