// PURPOSE: Draws one 2D-in-3D game object, feeding its position, rotation and
// other shape parameters into the graphics engine before drawing it.
//
// arg0 (a0): the render/scene context passed straight to DrawObject2D3D.
// arg1 (obj): the object's data. Fields used: +0x04 billboard matrix source,
//   +0x1c a 3-word vector, +0xa4 a 16-bit rotation angle, +0xb8 an fx32 value.
// It pushes several parameter blocks via func_01ff9048(id, ptr, count) (a
// graphics-register / uniform setter), builds a Z rotation 3x3 matrix from a
// sin/cos lookup table (data_0215d4b4) indexed by the angle, then draws the
// object using the shared shader/material pointer *data_0217b0b8.

typedef signed short s16;
typedef unsigned short u16;
typedef unsigned char u8;
typedef unsigned int u32;
typedef int fx32;

typedef struct {
    u8   _0[0x1c];
    fx32 v1c[3];              // 0x1c: 3-word vector
    u8   _28[0xa4 - 0x28];
    int  angle;              // 0xa4: rotation angle in the low 16 bits
    u8   _a8[0xb8 - 0xa8];
    fx32 fb8;               // 0xb8: fx32 scalar (shifted >>4 to a vector Y)
} Obj;

extern void func_01ff9048(int id, const void *ptr, int count);
extern void *MaybeGetBBMtxAtPosition(void *p);
extern void MTX_RotZ33__from_thumb(fx32 *dst, s16 sinv, s16 cosv);
extern void DrawObject2D3D(void *ctx, void *material, Obj *obj);

extern s16 data_0215d4b4[];   // sin/cos table, 2 shorts per angle step
extern void *data_0217b0b8;   // shared material/shader pointer

void func_020916a0(void *a0, Obj *obj)
{
    int reg1e = 0x1e;
    fx32 mtx[9];
    fx32 vec[3];
    int idx;

    func_01ff9048(0x14, &reg1e, 1);
    func_01ff9048(0x19, MaybeGetBBMtxAtPosition((u8 *)obj + 4), 0xc);

    vec[1] = obj->fb8 >> 4;
    vec[0] = 0;
    vec[2] = 0;
    func_01ff9048(0x1c, vec, 3);

    func_01ff9048(0x1b, obj->v1c, 3);

    idx = ((u16)obj->angle) >> 4;
    MTX_RotZ33__from_thumb(mtx, data_0215d4b4[idx * 2], data_0215d4b4[idx * 2 + 1]);
    func_01ff9048(0x1a, mtx, 9);

    DrawObject2D3D(a0, data_0217b0b8, obj);
}
