// PURPOSE: Rebuilds a kart movement direction from its current orientation.
// arg0 is the kart context and arg1 is the direction being adjusted.
// It removes the orientation component, normalizes the result when large enough,
// scales its horizontal components, and probably refreshes a perpendicular basis.

typedef int fx32;
typedef long long fx64;

typedef struct {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

#define FX_MUL(a, b) ((fx32)(((fx64)(a) * (fx32)(b)) >> 12))

typedef struct Ctx {
    char pad0[0x5c];
    fx32 f5c;
    fx32 f60;
    fx32 f64;
    char pad68[0xf0 - 0x68];
    VecFx32 fF0;
    char padFC[0x12c - 0xfc];
    fx32 f12c;
    VecFx32 f130;
    VecFx32 f13c;
    VecFx32 f148;
} Ctx;

extern fx32 Vector3_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b,
                             VecFx32 *out);
extern void Vector3_MaybeNormalize(const VecFx32 *in, VecFx32 *out);
extern void Vector3_Cross(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

void func_020f1d70(Ctx *ctx, const VecFx32 *dir)
{
    VecFx32 projection;
    VecFx32 *basis = &ctx->fF0;
    fx32 dot;

    ctx->f130.x = dir->x;
    ctx->f130.z = dir->z;

    dot = Vector3_DotProduct(basis, dir);
    projection.x = dir->x - FX_MUL(basis->x, dot);
    projection.y = dir->y - FX_MUL(basis->y, dot);
    projection.z = dir->z - FX_MUL(basis->z, dot);

    ctx->f13c.x = basis->x >> 2;
    ctx->f13c.y = basis->y >> 2;
    ctx->f13c.z = basis->z >> 2;
    VecFx32_Subtract(&projection, &ctx->f13c, &ctx->f13c);

    if ((fx64)ctx->f13c.x * ctx->f13c.x
        + (fx64)ctx->f13c.y * ctx->f13c.y
        + (fx64)ctx->f13c.z * ctx->f13c.z >= 0x10) {
        Vector3_MaybeNormalize(&ctx->f13c, &ctx->f13c);
    }

    {
        fx32 scale = ctx->f12c;
        ctx->f5c = FX_MUL(ctx->f13c.x, scale);
        ctx->f64 = FX_MUL(ctx->f13c.z, scale);
    }

    Vector3_Cross(dir, basis, &ctx->f148);
}
