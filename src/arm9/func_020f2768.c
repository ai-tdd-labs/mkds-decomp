// PURPOSE: Rebuilds a kart direction basis and plays its update sound.
// arg0 is a driver context and arg1 is the direction removed from its working vector.
// The result is normalized when large enough, copied to the saved direction, and crossed
// with another basis vector; the exact gameplay meaning of the extra subtraction is uncertain.

typedef int fx32;
typedef long long fx64;

typedef struct {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

#define FX_MUL(a, b) ((fx32)(((fx64)(a) * (fx32)(b)) >> 12))

typedef struct Ctx {
    char pad0[0xf0];
    VecFx32 fF0;
    char padFC[0x130 - 0xfc];
    VecFx32 f130;
    VecFx32 f13c;
    VecFx32 f148;
    char pad154[0x160 - 0x154];
    int f160;
} Ctx;

extern fx32 Vector3_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void Vector3_MaybeNormalize(const VecFx32 *in, VecFx32 *out);
extern void Vector3_Cross(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void DriverContext_MaybeQueuePlaySfx(Ctx *ctx, int event, int volume, int flags);

void func_020f2768(Ctx *ctx, const VecFx32 *dir)
{
    VecFx32 projection;
    VecFx32 *working = &ctx->f130;
    fx32 dot;

    dot = Vector3_DotProduct(dir, working);
    projection.x = FX_MUL(dir->x, dot);
    projection.y = FX_MUL(dir->y, dot);
    projection.z = FX_MUL(dir->z, dot);

    ctx->f130.x -= projection.x;
    working->y -= projection.y;
    working->z -= projection.z;

    if (ctx->f160 != 0)
        VecFx32_Subtract(working, &projection, working);

    if ((fx64)working->x * working->x
        + (fx64)working->y * working->y
        + (fx64)working->z * working->z >= 0x10)
        Vector3_MaybeNormalize(working, working);

    ctx->f13c = *working;
    Vector3_Cross(working, &ctx->fF0, &ctx->f148);
    ctx->fF0.y++;
    DriverContext_MaybeQueuePlaySfx(ctx, 0xd5, 0x7f, 0);
}
