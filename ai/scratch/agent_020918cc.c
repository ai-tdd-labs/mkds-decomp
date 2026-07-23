/*
 * PURPOSE: Draws one map object on screen, feeding its animation/matrix data
 * to the 3D geometry engine first.
 *
 * Args: r0 = render context/target, r1 = obj (a map-object state block).
 * It pushes three chunks of per-object data into the geometry engine via
 * func_01ff9048 (a small immediate 0x1e, the billboard matrix for the
 * object's position at obj+4, and 3 words at obj+0x1c), then sets the
 * object's NSBTP texture-pattern frame from a field reached through
 * obj->0x9c, and finally draws the object in 2D/3D.
 */

typedef unsigned short u16;
typedef unsigned int u32;

typedef struct { int x, y, z; } VecFx32;

typedef struct {
    u16 pad0[0x14];
    u16 frame;              /* 0x28: current animation frame */
} AnimState;

typedef struct {
    u32 pad00;
    VecFx32 pos;            /* 0x04: world position (billboard matrix source) */
    u32 pad10[3];
    u32 field1c[3];         /* 0x1c: 3-word block pushed to geometry engine */
    u32 pad28[(0x9c - 0x28) / 4];
    AnimState *anim;        /* 0x9c: pointer to animation state */
} MapObject;

extern void func_01ff9048(u32 id, const void *src, u32 count);
extern void *MaybeGetBBMtxAtPosition(const VecFx32 *pos);
extern void StructMapObject_SetNsbtpFrame(void *obj, u16 frame);
extern void DrawObject2D3D(void *ctx, void *obj, MapObject *o);

/* Global pointer to the shared map-object structure. */
extern void *data_0217b0bc;

void func_020918cc(void *ctx, MapObject *obj)
{
    u32 val = 0x1e;

    func_01ff9048(0x14, &val, 1);
    func_01ff9048(0x19, MaybeGetBBMtxAtPosition(&obj->pos), 0xc);
    func_01ff9048(0x1b, obj->field1c, 3);

    StructMapObject_SetNsbtpFrame(data_0217b0bc, obj->anim->frame);
    DrawObject2D3D(ctx, data_0217b0bc, obj);
}
