/*
 * PURPOSE: Draws one 2D/3D object, first feeding its per-object data
 * (position, a 12-word transform blob, and a few extra fields) into the
 * geometry engine.
 *
 * Args: r0 = render context/target, r1 = obj (an object state block).
 * It pushes a fixed id=0x1e marker, the object's position/quantized-scale
 * fields (obj->0x04/0x08/0x0c, right-shifted by 4 and stored back at
 * obj->0x4c/0x50/0x54 — probably a fixed-point unit conversion), the
 * 12-word transform blob at obj+0x28, and (when obj->0x11c == 1) an
 * extra 3-word block built from obj->0xbc/obj->0xdc, plus always the
 * 3-word block at obj+0x1c, all via func_01ff9048 (a small immediate-mode
 * geometry-engine data push). Finally it draws the object in 2D/3D.
 */

typedef unsigned int u32;

typedef struct {
    u32 pad00;               /* 0x00 */
    int posX;                /* 0x04 */
    int posY;                /* 0x08 */
    int posZ;                /* 0x0c */
    u32 pad10[3];             /* 0x10 */
    u32 field1c[3];           /* 0x1c: 3-word block pushed to geometry engine */
    u32 pad28[(0x4c - 0x28) / 4]; /* 0x28..0x4b: 12-word transform blob */
    int scaledX;              /* 0x4c: posX >> 4 */
    int scaledY;               /* 0x50: posY >> 4 */
    int scaledZ;                 /* 0x54: posZ >> 4 */
    u32 pad58[(0xbc - 0x58) / 4]; /* 0x58..0xbb */
    u32 fieldBC;                 /* 0xbc */
    u32 pad_c0[(0xdc - 0xc0) / 4]; /* 0xc0..0xdb */
    u32 fieldDC;                    /* 0xdc */
    u32 pad_e0[(0x11c - 0xe0) / 4]; /* 0xe0..0x11b */
    int mode;                        /* 0x11c: extra-push flag (1 => push) */
} DrawObj;

extern void func_01ff9048(u32 id, const void *src, u32 count);
extern void DrawObject2D3D(void *ctx, void *scene, void *obj);

/* Global pointer to the shared scene/material handle. */
extern void *data_0217b180;

void func_0209c678(void *ctx, DrawObj *obj)
{
    u32 val = 0x1e;

    func_01ff9048(0x14, &val, 1);

    obj->scaledX = obj->posX >> 4;
    obj->scaledY = obj->posY >> 4;
    obj->scaledZ = obj->posZ >> 4;
    func_01ff9048(0x19, &obj->pad28[0], 0xc);

    if (obj->mode == 1) {
        u32 a = obj->fieldBC;
        u32 b = obj->fieldDC;
        u32 tmp[3];
        tmp[0] = a;
        tmp[1] = b;
        tmp[2] = a;
        func_01ff9048(0x1b, tmp, 3);
    }

    func_01ff9048(0x1b, obj->field1c, 3);

    DrawObject2D3D(ctx, data_0217b180, obj);
}
