/* PURPOSE: Draws one tilted 2D/3D track object (a twin of func_02093a50), building
 *          its geometry command list and pitching it to match its angle.
 *
 * arg0 (r5): the render/scene context passed straight through to the draw calls.
 * arg1 (obj, r4): the object instance. If its state field at +0xb0 is not exactly
 *          2 the object is skipped. Otherwise: a header word (0x1e) is pushed,
 *          the object's position (+4,+8,+0xc, each >>4) is written into the
 *          +0x28 block which is then pushed (0xc words), a 3-word block at +0x1c
 *          is pushed, the object is drawn once, then an X-axis rotation matrix
 *          built from FX_Atan2(-obj->+0x14, 0xc000) is pushed and the object is
 *          drawn again (second material). func_01ff9048 is the display-list writer.
 */

typedef signed char        s8;
typedef unsigned char      u8;
typedef signed short       s16;
typedef unsigned short     u16;
typedef signed int         s32;
typedef unsigned int       u32;

typedef struct { s32 m[9]; } MtxFx33;   /* 9 fx32 words = the count-9 block */

extern void  func_01ff9048(int cmd, const void *data, int count);
extern int   FX_Atan2(int y, int x);
extern void  MTX_RotX33__from_thumb(MtxFx33 *mtx, s16 sinv, s16 cosv);
extern void  DrawObject2D3D(void *ctx, void *obj2, void *obj);

extern s16   data_0215d4b4[];   /* sin/cos table: [idx*2]=sin, [idx*2+1]=cos */
extern void *data_0217b0e0;     /* first object template pointer  */
extern void *data_0217b0e4;     /* second object template pointer */

void func_02095848(void *ctx, void *obj)
{
    int v;
    MtxFx33 mtx;
    int idx;

    if (*(int *)((u8 *)obj + 0xb0) != 2)
        return;

    v = 0x1e;
    func_01ff9048(0x14, &v, 1);

    *(s32 *)((u8 *)obj + 0x4c) = *(s32 *)((u8 *)obj + 0x4) >> 4;
    *(s32 *)((u8 *)obj + 0x50) = *(s32 *)((u8 *)obj + 0x8) >> 4;
    *(s32 *)((u8 *)obj + 0x54) = *(s32 *)((u8 *)obj + 0xc) >> 4;
    func_01ff9048(0x19, (u8 *)obj + 0x28, 0xc);

    func_01ff9048(0x1b, (u8 *)obj + 0x1c, 3);

    DrawObject2D3D(ctx, data_0217b0e0, obj);

    idx = (u16)FX_Atan2(-*(int *)((u8 *)obj + 0x14), 0xc000) >> 4;
    MTX_RotX33__from_thumb(&mtx, data_0215d4b4[idx * 2], data_0215d4b4[idx * 2 + 1]);
    func_01ff9048(0x1a, &mtx, 9);

    DrawObject2D3D(ctx, data_0217b0e4, obj);
}
