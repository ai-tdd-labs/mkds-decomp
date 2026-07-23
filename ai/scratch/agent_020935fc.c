/* PURPOSE: Draws one map object on screen: gives it a fresh polygon id, feeds
 *          its position/matrix/parameter blocks to the geometry engine, then
 *          draws its 3D model plus 2D icon.
 *
 * Args: a0 = render/scene context (passed straight to DrawObject2D3D),
 *       obj = the map object to draw.
 * Behaviour: if obj->fa8 (a count/flag) is <= 0 the object is skipped.
 *   Otherwise it assigns a rolling polygon id (func_020d3c44 returns/advances a
 *   global counter) to the shared render handle *data_0217b0c8, then pushes
 *   five parameter blocks into the geometry-command helper func_01ff9048
 *   (cmd, ptr, count): a constant 0x1e, the billboard matrix for the object's
 *   position at obj+4, a {0, obj->f5c>>4, 0} vector, obj->fa8 repeated 3x, and
 *   the 3 words at obj->f1c. Finally it sets a field from obj->fa4 and draws.
 *   data_0217b0c8 is a global pointer reloaded (dereffed) for each use.
 */

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    char _0[0x1c];
    int  f1c[3];        /* 0x1c: 3-word param block (cmd 0x1b) */
    char _28[0x5c - 0x28];
    int  f5c;           /* 0x5c: fx32 value, shifted >>4 into a vector Y */
    char _60[0xa4 - 0x60];
    u16  fa4;           /* 0xa4: a 16-bit field */
    char _a6[0xa8 - 0xa6];
    int  fa8;           /* 0xa8: count/flag; must be > 0 to draw, repeated 3x */
} Obj;

extern void func_01ff9048(int cmd, const void *ptr, int count);
extern int  func_020d3c44(void);
extern void *MaybeGetBBMtxAtPosition(void *p);
extern void StructMapObject_MaybeSetPolygonId(void *handle, int id);
extern void StructMapObject_SomeFn_3(void *handle, u16 v);
extern void DrawObject2D3D(void *ctx, void *handle, Obj *obj);

extern void *data_0217b0c8;   /* shared render handle (pointer global) */

void func_020935fc(void *a0, Obj *obj)
{
    int v;              /* sp+0    */
    int vec[3];         /* sp+4/8/c */
    int t[3];           /* sp+10/14/18 */

    if (obj->fa8 <= 0)
        return;

    StructMapObject_MaybeSetPolygonId(data_0217b0c8, func_020d3c44());

    v = 0x1e;
    func_01ff9048(0x14, &v, 1);

    func_01ff9048(0x19, MaybeGetBBMtxAtPosition((u8 *)obj + 4), 0xc);

    vec[1] = obj->f5c >> 4;
    vec[0] = 0;
    vec[2] = 0;
    func_01ff9048(0x1c, vec, 3);

    t[0] = obj->fa8;
    t[1] = t[0];
    t[2] = t[0];
    func_01ff9048(0x1b, t, 3);

    func_01ff9048(0x1b, obj->f1c, 3);

    StructMapObject_SomeFn_3(data_0217b0c8, obj->fa4);

    DrawObject2D3D(a0, data_0217b0c8, obj);
}
