/* PURPOSE: Draws one spinning 2D/3D track object (like an item box or sign),
 *          building its geometry command list and rotating it to face its angle.
 *
 * arg0 (r5): the render/scene context passed straight through to the draw calls.
 * arg1 (obj, r4): the object instance. If its "active/count" field at +0xa0 is
 *          zero or negative the object is skipped. Otherwise four geometry
 *          command chunks are pushed via func_01ff9048 (a display-list writer):
 *          a header word (0x1e), a 0xc-word block fetched via func_020e6b58,
 *          a 3x3 rotation matrix built from the object's angle, and a 3-word
 *          block at +0x1c. Finally the object is drawn twice (two materials).
 */

typedef signed char        s8;
typedef unsigned char      u8;
typedef signed short       s16;
typedef unsigned short     u16;
typedef signed int         s32;
typedef unsigned int       u32;

typedef struct { s32 m[9]; } MtxFx33;   /* 9 fx32 words = the count-9 block */

extern void  func_01ff9048(int cmd, const void *data, int count);
extern void *func_020e6b58(void *p);
extern void  MTX_RotY33__from_thumb(MtxFx33 *mtx, s16 sinv, s16 cosv);
extern void  DrawObject2D3D(void *ctx, void *obj2, void *obj);

extern s16   data_0215d4b4[];   /* sin/cos table: [idx*2]=sin, [idx*2+1]=cos */
extern void *data_0217b0d0;     /* first object template pointer  */
extern void *data_0217b0cc;     /* second object template pointer */

void func_02093a50(void *ctx, void *obj)
{
    int x;
    MtxFx33 mtx;
    int idx;

    if (*(int *)((u8 *)obj + 0xa0) <= 0)
        return;

    x = 0x1e;
    func_01ff9048(0x14, &x, 1);

    func_01ff9048(0x19, func_020e6b58((u8 *)obj + 4), 0xc);

    idx = (int)*(u16 *)((u8 *)obj + 0x7e) >> 4;
    MTX_RotY33__from_thumb(&mtx, data_0215d4b4[idx * 2], data_0215d4b4[idx * 2 + 1]);
    func_01ff9048(0x1a, &mtx, 9);

    func_01ff9048(0x1b, (u8 *)obj + 0x1c, 3);

    DrawObject2D3D(ctx, data_0217b0d0, obj);
    DrawObject2D3D(ctx, data_0217b0cc, obj);
}
