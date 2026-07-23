// PURPOSE: Places an object at a racer-relative position and copies its direction.
// obj receives the translated world position and a 16-bit direction vector.
// ctx supplies the base position, movement vector, and distance scale.

typedef short s16;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} VecFx16;

typedef struct {
    int f0;
    int f4;
    int f8;
    int fc;
} NodeB;

typedef struct {
    char pad00[0x80];
    VecFx32 f80;
    char pad8c[0x138 - 0x8c];
    VecFx32 f138;
    char pad144[0x1d0 - 0x144];
    int f1d0;
} Ctx;

typedef struct {
    char pad00[0x20];
    NodeB **f20;
    char pad24[0x28 - 0x24];
    int f28;
    int f2c;
    int f30;
    char pad34[0x50 - 0x34];
    VecFx16 f50;
} Obj;

extern void VecFx32_AddScale1(int scale, VecFx32 *direction,
                              VecFx32 *source, VecFx32 *destination);

void func_0206c1ac(Obj *obj, Ctx *ctx)
{
    VecFx16 direction;
    VecFx32 position;
    VecFx32 *directionSource;

    position = ctx->f80;
    VecFx32_AddScale1(
        (int)(((long long)ctx->f1d0 * -0x1333 + 0x800) >> 12),
        &ctx->f138, &position, &position);

    position.x >>= 4;
    position.y >>= 4;
    position.z >>= 4;

    directionSource = &ctx->f138;

    obj->f28 = (*obj->f20)->f4 + position.x;
    obj->f2c = position.y + (*obj->f20)->f8;
    obj->f30 = position.z + (*obj->f20)->fc;

    direction.x = (s16)ctx->f138.x;
    direction.y = (s16)directionSource->y;
    direction.z = (s16)directionSource->z;
    obj->f50 = direction;
}
