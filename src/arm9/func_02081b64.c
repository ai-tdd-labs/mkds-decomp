/*
 * PURPOSE: Positions and aims a racer's trailing effect (like a drift smoke or
 * draft object) behind the kart each frame.
 *
 * Args: obj = the effect object (r0), ctx = the racer/context struct (r1),
 * a2 (r2) and a3 (r3) = two fx32 steering/velocity scalars.
 * It takes the base point ctx->f508 (scaled down by 16), then slides it along
 * two direction vectors (ctx->f138 by fx-mul(ctx->fc4,a3) and ctx->f12c by
 * fx-mul(ctx->fc0,a2)) to build an offset position. That offset plus the node
 * transform (obj->f20) is written to obj->f28..f30. Finally it fetches a facing
 * vector via GetMQRacerVector333, negates it, and stores it (truncated to 16-bit)
 * at obj->f50..f54.
 */

typedef unsigned short u16;
typedef short s16;

typedef struct { int x, y, z; } VecFx32;   /* fx32 3-vector */
typedef struct { s16 x, y, z; } VecFx16;   /* fx16 3-vector */

typedef struct { int f0, f4, f8, fc; } NodeB;

typedef struct {
    char pad00[0xc0];
    int fc0;            /* +0xc0 scalar */
    int fc4;            /* +0xc4 scalar */
    char pad_c8[0x12c - 0xc8];
    VecFx32 f12c;       /* +0x12c direction vector */
    VecFx32 f138;       /* +0x138 direction vector */
    char pad144[0x508 - 0x144];
    VecFx32 *f508;      /* +0x508 base position */
} Ctx;

typedef struct {
    char pad00[0x20];
    NodeB **f20;        /* +0x20 -> node transform */
    char pad24[0x28 - 0x24];
    int f28, f2c, f30;  /* +0x28 world position */
    char pad34[0x50 - 0x34];
    VecFx16 f50;        /* +0x50 facing, 16-bit */
} Obj;

extern void VecFx32_AddScale1(int scale, VecFx32 *v, VecFx32 *src, VecFx32 *out);
extern void GetMQRacerVector333(Ctx *ctx, VecFx32 *out);

void func_02081b64(Obj *obj, Ctx *ctx, int a2, int a3)
{
    VecFx16 dir;
    VecFx32 off;
    VecFx32 nrm;

    VecFx32 *base = ctx->f508;
    off.x = base->x >> 4;
    off.y = base->y >> 4;
    off.z = base->z >> 4;

    VecFx32_AddScale1((int)(((long long)ctx->fc4 * a3 + 0x800) >> 12),
                      &ctx->f138, &off, &off);
    VecFx32_AddScale1((int)(((long long)ctx->fc0 * a2 + 0x800) >> 12),
                      &ctx->f12c, &off, &off);

    obj->f28 = off.x + (*obj->f20)->f4;
    obj->f2c = off.y + (*obj->f20)->f8;
    obj->f30 = off.z + (*obj->f20)->fc;

    GetMQRacerVector333(ctx, &nrm);

    nrm.x = -nrm.x; dir.x = (s16)nrm.x;
    nrm.y = -nrm.y; dir.y = (s16)nrm.y;
    nrm.z = -nrm.z; dir.z = (s16)nrm.z;

    obj->f50 = dir;
}
