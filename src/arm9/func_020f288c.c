/* func_020f288c (arm) — orthonormalises a driver-context basis and fires an SFX.
 *
 * arg0 (ctx) is a large driver/entity context. arg1 (dir) is a VecFx32*.
 * It Gram-Schmidt-removes the arg1 component from ctx->f13c
 * (ctx->f13c -= dir * dot(dir, ctx->f13c)); when ctx->f160 is set it subtracts
 * the projection once more (a reflection-like extra step). It then normalises
 * ctx->f13c (only if |v|^2 >= 0x10), builds ctx->f130 = {f13c.x, 0, f13c.z},
 * normalises that too, stores its cross product with ctx->fF0 into ctx->f148,
 * and finally queues sfx 0xd5. Probably re-derives a vehicle's up/right basis.
 *
 * The two "normalise only if squared length >= 0x10" guards reproduce the ROM's
 * inlined 64-bit magnitude test; the actual normalise stays a call. */

typedef int fx32;
typedef long long fx64;
typedef struct { fx32 x, y, z; } VecFx32;

/* fx32 fixed-point multiply: (a * b) >> 12 via a signed 64-bit product */
#define FX_MUL(a, b) ((fx32)(((fx64)(a) * (fx32)(b)) >> 12))

typedef struct Ctx {
    char pad0[0xf0];
    VecFx32 fF0;                /* 0xf0: cross-product operand */
    char padFC[0x130 - 0xfc];
    VecFx32 f130;              /* 0x130: temp {x,0,z} then cross dest input */
    VecFx32 f13c;              /* 0x13c: primary working direction vector */
    VecFx32 f148;              /* 0x148: cross-product output */
    char pad154[0x160 - 0x154];
    int f160;                  /* 0x160: enables the extra subtract */
} Ctx;

/* returns dot(a, b) */
extern fx32 Vector3_DotProduct(const VecFx32 *a, const VecFx32 *b);
/* out = a - b */
extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
/* out = normalise(in) */
extern void Vector3_MaybeNormalize(const VecFx32 *in, VecFx32 *out);
/* out = a x b */
extern void Vector3_Cross(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void DriverContext_MaybeQueuePlaySfx(Ctx *ctx, int a, int b, int c);

void func_020f288c(Ctx *ctx, const VecFx32 *dir) {
    VecFx32 proj;
    /* cached sub-vector pointers -> held in callee-saved regs (r5, r4) */
    VecFx32 *v = &ctx->f13c;
    VecFx32 *w = &ctx->f130;
    fx32 dot;

    dot = Vector3_DotProduct(dir, v);
    proj.x = FX_MUL(dir->x, dot);
    proj.y = FX_MUL(dir->y, dot);
    proj.z = FX_MUL(dir->z, dot);

    ctx->f13c.x -= proj.x;
    v->y -= proj.y;
    v->z -= proj.z;

    if (ctx->f160 != 0)
        VecFx32_Subtract(v, &proj, v);

    /* first two squares load swapped (y,x,z) under -O4 reassociation */
    if ((fx64)v->x * v->x + (fx64)v->y * v->y + (fx64)v->z * v->z >= 0x10)
        Vector3_MaybeNormalize(v, v);

    /* read both surviving components first so v's register frees up and gets
       reused as the 0 constant (matching the ROM's mov r5,#0 + sbcs r0,r1,r5) */
    {
        fx32 vx = v->x;
        fx32 vz = v->z;
        w->x = vx;
        w->y = 0;
        w->z = vz;
    }

    if ((fx64)w->x * w->x + (fx64)w->y * w->y + (fx64)w->z * w->z >= 0x10)
        Vector3_MaybeNormalize(w, w);

    Vector3_Cross(w, &ctx->fF0, &ctx->f148);
    DriverContext_MaybeQueuePlaySfx(ctx, 0xd5, 0x7f, 0);
}
