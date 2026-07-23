/*
 * PURPOSE: Converts an object's raw position into draw-scale units, logs some
 * debug info about it, then hands it off to the 3D object renderer.
 *
 * arg0 (ctx)  - opaque context/list pointer, forwarded unchanged to
 *               DrawObject2D3D.
 * arg1 (obj)  - object struct. Its raw fixed-point position fields at +0x4,
 *               +0x8, +0xc (probably 1/4096 fixed point) are rescaled by >>4
 *               and stored back at +0x4c/+0x50/+0x54 (1/256 fixed point).
 *               Field +0x11c is probably a mode flag: when it equals 1, an
 *               extra debug dump of fields +0xbc/+0xdc runs. Field +0xa0 is
 *               a u16 nsbtp animation frame index.
 *
 * func_01ff9048 is an unnamed itcm debug/log routine, called here as
 * func_01ff9048(tag, argsPtr, n) purely for its side effects (probably an
 * internal assert/telemetry logger); its exact semantics don't affect the
 * observable behaviour of this function.
 */

extern void func_01ff9048(int tag, void *args, int n);
extern void StructMapObject_SetNsbtpFrame(void *model, unsigned short frame);
extern void DrawObject2D3D(void *ctx, void *model, void *obj);

extern void *data_0217b184;

void func_0209c7a8(void *ctx, unsigned char *obj)
{
    int buf[5];

    buf[0] = 0x1e;
    func_01ff9048(0x14, &buf[0], 1);

    *(int *)(obj + 0x4c) = *(int *)(obj + 0x4) >> 4;
    *(int *)(obj + 0x50) = *(int *)(obj + 0x8) >> 4;
    *(int *)(obj + 0x54) = *(int *)(obj + 0xc) >> 4;
    func_01ff9048(0x19, obj + 0x28, 0xc);

    if (*(int *)(obj + 0x11c) == 1) {
        int a = *(int *)(obj + 0xbc);
        int b = *(int *)(obj + 0xdc);
        buf[1] = a;
        buf[2] = b;
        buf[3] = a;
        func_01ff9048(0x1b, &buf[1], 3);
    }

    func_01ff9048(0x1b, obj + 0x1c, 3);

    StructMapObject_SetNsbtpFrame(data_0217b184, *(unsigned short *)(obj + 0xa0));
    DrawObject2D3D(ctx, data_0217b184, obj);
}
