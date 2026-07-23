/*
 * PURPOSE: Draws one map object on screen, feeding its animation/matrix and
 * shadow-plane data to the 3D geometry engine first.
 *
 * Args: r0 = render context/target, r1 = obj (a map-object state block).
 * It pushes four chunks of per-object data into the geometry engine via
 * func_01ff9048: a small immediate 0x1e, the billboard matrix for the
 * object's position at obj+4, a 3-word shadow-plane block derived from the
 * object's ground-height fields at obj+0x1e8/obj+0x1f0, and the 3 words at
 * obj+0x1c, then finally draws the object in 2D/3D.
 */

typedef unsigned short u16;
typedef unsigned int u32;

typedef struct { int x, y, z; } VecFx32;

typedef struct {
    u32 pad00;
    VecFx32 pos;             /* 0x04: world position (billboard matrix source) */
    u32 pad10[3];
    u32 field1c[3];          /* 0x1c: 3-word block pushed to geometry engine */
    u32 pad28[(0x1e8 - 0x28) / 4];
    u32 groundLo;            /* 0x1e8: lower ground-height bound */
    u32 pad1ec;
    u32 groundHi;            /* 0x1f0: upper ground-height bound */
} MapObject;

extern void func_01ff9048(u32 id, const void *src, u32 count);
extern void *MaybeGetBBMtxAtPosition(const VecFx32 *pos);
extern void DrawObject2D3D(void *ctx, void *obj, MapObject *o);

/* Global pointer to the shared map-object structure. */
extern void *data_0217b10c;

void func_02098954(void *ctx, MapObject *obj)
{
    u32 span;
    u32 hi;
    u32 lo = obj->groundLo;
    hi = obj->groundHi;
    span = (0x3000 - lo) - hi;
    u32 val = 0x1e;

    func_01ff9048(0x14, &val, 1);
    func_01ff9048(0x19, MaybeGetBBMtxAtPosition(&obj->pos), 0xc);

    {
        u32 base = lo + hi - 0x1000;
        u32 shadow[3];
        shadow[1] = base;
        shadow[0] = span;
        shadow[2] = span;
        func_01ff9048(0x1b, &shadow[0], 3);
    }

    func_01ff9048(0x1b, obj->field1c, 3);

    DrawObject2D3D(ctx, data_0217b10c, obj);
}
