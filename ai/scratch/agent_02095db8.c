/* PURPOSE: Draws one map object (its 3D model, choosing near/far draw path by
 *          distance-flag) and, unless a distance flag is set, also updates its
 *          shadow/trail sub-object.
 *
 * Arguments: ctx (r7) = render/scene context passed straight through to the
 *   draw calls, o (r6) = the map object, a2/a3 (r5/r4) = extra params forwarded
 *   to func_020e53ac.
 * Behaviour: pushes the usual three drawing-parameter blocks (id 0x14 header,
 *   id 0x19 bounding box computed from the object position, id 0x1b block at
 *   +0x1c) via func_01ff9048, exactly like the sibling draw helpers. It then
 *   masks off the priority/scratch bits of the flag word at +0x78 and compares
 *   the remainder against a threshold: below it, the object's nsbca animation
 *   frame is applied and it is drawn through the normal manager; at or above
 *   it, it is drawn through func_0209ba58 instead (an alternate/simplified
 *   path). Finally the same masked flag word is checked against a second,
 *   larger threshold; if it is still below that, the object's secondary
 *   sub-object at +0xdc is updated and stepped via func_020e5668/func_020e53ac.
 */

typedef unsigned short u16;
typedef unsigned int   u32;
typedef int             s32;

typedef struct Obj {
    char _0[4];
    s32 f4;                 /* world X (fx32) */
    char _8[0x14];
    s32 f1c;                /* param block for id 0x1b (3 entries) */
    char _20[0x58];
    s32 f78;                /* status/priority flags */
    char _7c[0x30];
    u16 fac;                /* nsbca animation frame */
    char _ae[0x2e];
    char fdc[1];             /* secondary sub-object block */
} Obj;

extern void  func_01ff9048(int id, const void *data, int count);
extern void *MaybeGetBBMtxAtPosition(const s32 *pos);
extern void  StructMapObject_MaybeSetNsbcaFrame(void *mgr, u16 frame);
extern void  DrawObject2D3D(void *ctx, void *mgr, Obj *o);
extern void  func_0209ba58(void *ctx, void *mgr, Obj *o);
extern void  func_020e5668(void *dst, void *src);
extern void  func_020e53ac(void *sub, int flag, void *a2, void *a3);

extern void *data_0217b0e8;

void func_02095db8(void *ctx, Obj *o, void *a2, void *a3)
{
    volatile int hdr;
    void *bbmtx;
    s32 masked;

    hdr = 0x1e;
    func_01ff9048(0x14, (void *)&hdr, 1);

    bbmtx = MaybeGetBBMtxAtPosition(&o->f4);
    func_01ff9048(0x19, bbmtx, 0xc);

    func_01ff9048(0x1b, &o->f1c, 3);

    masked = o->f78 & ~0xc000001fu;
    if (masked < 0xc5c10) {
        StructMapObject_MaybeSetNsbcaFrame(data_0217b0e8, o->fac);
        DrawObject2D3D(ctx, data_0217b0e8, o);
    } else {
        func_0209ba58(ctx, data_0217b0e8, o);
    }

    masked = o->f78 & ~0xc000001fu;
    if (masked >= 0x27100)
        return;

    func_020e5668(&o->fdc, &o->f4);
    func_020e53ac(&o->fdc, 0, a2, a3);
}
