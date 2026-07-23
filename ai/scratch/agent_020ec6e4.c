// PURPOSE: Builds a scaled sideways direction vector between two objects.

typedef int fx32;
typedef long long fx64;

typedef struct {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct {
    char pad0[4];
    VecFx32 f4;
    VecFx32 f10;
    char pad1c[0xa8 - 0x1c];
    int fA8;
    char padac[0xb0 - 0xac];
    fx32 fB0;
    fx32 fB4;
} Work;

typedef struct {
    char pad0[0x50];
    fx32 f50;
    char pad54[0x58 - 0x54];
    fx32 f58;
    char pad5c[0x80 - 0x5c];
    VecFx32 f80;
    char pad8c[0xa4 - 0x8c];
    fx32 fA4;
    char pada8[0xac - 0xa8];
    fx32 fAC;
} Other;

extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

#define FX_MUL(a, b) ((fx32)(((fx64)(a) * (b)) >> 12))

void func_020ec6e4(Work *work, Other *other)
{
    VecFx32 direction;
    fx64 p1;
    fx64 p2;

    VecFx32_Subtract(&work->f4, &other->f80, &direction);
    p1 = (fx64)direction.z * other->fA4;
    p2 = (fx64)direction.x * other->fAC;
    if (p1 - p2 >= 0)
        goto nonnegative;

    direction.z = -other->f50;
    direction.x = other->f58;
    direction.y = 0;
    work->fA8 = 1;
    goto done;

nonnegative:
    direction.z = other->f50;
    direction.x = -other->f58;
    direction.y = 0;
    work->fA8 = 0;

done:
    work->f10.x = FX_MUL(direction.x, work->fB4);
    work->f10.y = FX_MUL(direction.y, work->fB4);
    work->f10.z = FX_MUL(direction.z, work->fB4);
    work->f10.x += other->fA4 >> 1;
    work->f10.z += other->fAC >> 1;
    work->f10.y = work->fB0;
}
