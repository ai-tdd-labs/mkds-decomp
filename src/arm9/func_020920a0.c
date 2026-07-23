/* PURPOSE: Draws one map object on screen (its 3D model plus its 2D icon).
 *
 * Arguments: a0 = the render/scene context, o = the map object to draw.
 * Behaviour: tells the object's model which animation frame to show, sets up
 *   three drawing parameter blocks (via func_01ff9048), copies the object's
 *   world position (x,y,z at +4/+8/+c) shifted right 4 into +0x4c/+0x50/+0x54,
 *   then hands everything to DrawObject2D3D. data_0217b0c0 is a global handle
 *   (probably the current model/render manager) reloaded for each use.
 */

typedef struct Obj {
    char _0[4];
    int f4;                 /* world X (fx32) */
    int f8;                 /* world Y (fx32) */
    int fc;                 /* world Z (fx32) */
    char _10[0xc];
    int f1c;                /* param block for id 0x1b (3 entries) */
    char _20[8];
    int f28;                /* param block for id 0x19 (0xc entries) */
    char _2c[0x20];
    int f4c;                /* X >> 4 */
    int f50;                /* Y >> 4 */
    int f54;                /* Z >> 4 */
    char _58[0x48];
    unsigned short fa0;     /* nsbca animation frame */
} Obj;

extern void *data_0217b0c0;

extern void StructMapObject_MaybeSetNsbcaFrame(void *mgr, unsigned short frame);
extern void func_01ff9048(int id, void *ptr, int count);
extern void DrawObject2D3D(void *ctx, void *mgr, Obj *o);

void func_020920a0(void *a0, Obj *o)
{
    volatile int frameId;

    StructMapObject_MaybeSetNsbcaFrame(data_0217b0c0, o->fa0);
    frameId = 0x1e;
    func_01ff9048(0x14, (void *)&frameId, 1);

    o->f4c = o->f4 >> 4;
    o->f50 = o->f8 >> 4;
    o->f54 = o->fc >> 4;
    func_01ff9048(0x19, &o->f28, 0xc);
    func_01ff9048(0x1b, &o->f1c, 3);

    DrawObject2D3D(a0, data_0217b0c0, o);
}
