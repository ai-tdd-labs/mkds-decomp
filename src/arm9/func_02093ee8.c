/* PURPOSE: Draws one 2D/3D object on screen, first uploading its geometry
 * settings (transform matrix + a couple of parameter blocks) to the 3D engine.
 *
 * arg0: the render target / context passed straight through to DrawObject2D3D.
 * arg1: the object. Its position fields (x,y,z at +4,+8,+0xc) are shifted right
 *   by 4 (fx32 -> smaller fixed point) and written into the translation row of
 *   the object's 4x3 matrix at +0x28, then three parameter blocks are pushed to
 *   the geometry engine via func_01ff9048(id, ptr, wordcount) before drawing.
 * func_01ff9048 probably writes `count` words from `src` to geometry unit `id`.
 */

typedef struct {
    int _00;          /* 0x00 */
    int pos_x;        /* 0x04 */
    int pos_y;        /* 0x08 */
    int pos_z;        /* 0x0c */
    int _10[3];       /* 0x10 */
    int blk1[3];      /* 0x1c  (uploaded with id 0x1b, 3 words) */
    int mtx[9];       /* 0x28  (start of 12-word 4x3 matrix, uploaded id 0x19) */
    int m_tx;         /* 0x4c  translation x */
    int m_ty;         /* 0x50  translation y */
    int m_tz;         /* 0x54  translation z */
} Obj;

extern void func_01ff9048(int id, const void *src, int count);
extern void DrawObject2D3D(void *ctx, void *p, Obj *o);
extern void *data_0217b0d4;

void func_02093ee8(void *ctx, Obj *o)
{
    int local = 0x1e;

    func_01ff9048(0x14, &local, 1);
    func_01ff9048(0x1b, o->blk1, 3);

    o->m_tx = o->pos_x >> 4;
    o->m_ty = o->pos_y >> 4;
    o->m_tz = o->pos_z >> 4;

    func_01ff9048(0x19, o->mtx, 0xc);

    DrawObject2D3D(ctx, data_0217b0d4, o);
}
