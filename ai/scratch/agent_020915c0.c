/* PURPOSE: Sends a game object's 3D graphics data to the display, then draws it on screen.
 *
 * arg0 (r5): a render/context handle passed straight through to DrawObject2D3D.
 * arg1 (r4): pointer to the object being drawn; we feed several of its fields
 *            (a matrix-ish thing at +4, data at +0x1c, and a value at +0xb4)
 *            into the geometry-command helper func_01ff9048 before drawing.
 * func_01ff9048(cmd, ptr, count) probably packs `count` words from `ptr`
 * into a graphics/geometry command buffer under command id `cmd`.
 * The final draw uses a global scene pointer stored in data_0217b0b4.
 */

typedef unsigned char u8;

extern void func_01ff9048(int cmd, void *ptr, int count);
extern void *MaybeGetBBMtxAtPosition(void *p);
extern void DrawObject2D3D(void *ctx, void *scene, void *obj);

extern void *data_0217b0b4;

void func_020915c0(void *arg0, void *arg1)
{
    int v = 0x1e;   /* sp+0 */
    int t[3];       /* sp+4, sp+8, sp+0xc */

    func_01ff9048(0x14, &v, 1);
    func_01ff9048(0x19, MaybeGetBBMtxAtPosition((u8 *)arg1 + 4), 0xc);
    func_01ff9048(0x1b, (u8 *)arg1 + 0x1c, 3);

    t[0] = *(int *)((u8 *)arg1 + 0xb4);
    t[1] = t[0];
    t[2] = t[0];
    func_01ff9048(0x1b, t, 3);

    DrawObject2D3D(arg0, data_0217b0b4, arg1);
}
