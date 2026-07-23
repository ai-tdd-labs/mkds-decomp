typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef signed int fx32;
typedef signed long long fx64;

#define reg_CP_SQRTCNT      (*(volatile u16 *)0x040002B0)
#define reg_CP_SQRT_RESULT  (*(volatile u32 *)0x040002B4)
#define reg_CP_SQRT_PARAM   (*(volatile u64 *)0x040002B8)

typedef struct VecFx32 {
    fx32 x, y, z;
} VecFx32;

fx32 VecFx32_Norm(VecFx32 *a)
{
    fx64 l2 = (fx64)a->x * a->x;
    l2 += (fx64)a->y * a->y;
    l2 += (fx64)a->z * a->z;
    reg_CP_SQRTCNT = 0x1;
    reg_CP_SQRT_PARAM = (u64)(l2 * 4);
    while (reg_CP_SQRTCNT & 0x8000) {}
    return ((fx32)reg_CP_SQRT_RESULT + 1) >> 1;
}
