/* Draws a single textured quad (billboard-like strip) through the NDS 3D
 * geometry engine using immediate-mode MMIO register writes.
 *
 * Builds two 4x3 model matrices m0/m1 from the camera matrix `cam`:
 *   each is a scale (Y from top->_08 / bottom->_08, X/Z = 1.0) whose
 *   translation column is taken from top->pos / bottom->pos, then
 *   concatenated with `cam` in place.
 * Then it begins a primitive, loads m0, emits the top edge (2 verts),
 * loads m1, emits the bottom edge (2 verts) and ends the primitive.
 * Texture S/T come from tex->s (0x1c) and tex->t (0x20): each is converted
 * to a 16-bit texcoord via (x<<8)>>16 then truncated to u16.
 * Vertex XY positions are fixed 10-bit constants (+/-0.125 in Y).
 * args: cam = view/proj MtxFx43*; top/bottom = corner params (scale+pos);
 *        tex = texture-size params (s at 0x1c, t at 0x20). */

typedef int fx32;

typedef struct { fx32 x, y, z; } VecFx32;

/* NITRO 4x3 fixed-point matrix: 3x3 rotation then translation column. */
typedef struct {
    fx32 _00, _01, _02;
    fx32 _10, _11, _12;
    fx32 _20, _21, _22;
    fx32 _30, _31, _32;   /* translation at 0x24 / 0x28 / 0x2c */
} MtxFx43;

/* Corner descriptor: Y-scale at 0x08, position vector at 0x10..0x18. */
typedef struct {
    fx32 _00, _04;
    fx32 scaleY;          /* 0x08 */
    fx32 _0c;
    VecFx32 pos;          /* 0x10, 0x14, 0x18 */
} Corner;

/* Texture-size params: S at 0x1c, T at 0x20. */
typedef struct {
    char _pad[0x1c];
    fx32 s;               /* 0x1c */
    fx32 t;               /* 0x20 */
} TexParam;

extern void MTX_Scale43__from_thumb(MtxFx43 *m, fx32 x, fx32 y, fx32 z);
extern void MTX_Concat43(const MtxFx43 *a, const MtxFx43 *b, MtxFx43 *ab);
extern void G3_LoadMtx43(const MtxFx43 *m);

/* Geometry-engine registers (direct volatile MMIO, no extern symbols). */
#define REG_GE_BEGIN    (*(volatile unsigned long *)0x04000500)
#define REG_GE_END      (*(volatile unsigned long *)0x04000504)
#define REG_GE_TEXCOORD (*(volatile unsigned long *)0x04000488)
#define REG_GE_VTX_10   (*(volatile unsigned long *)0x04000490)

void func_0208e82c(MtxFx43 *cam, Corner *top, Corner *bottom, TexParam *tex) {
    MtxFx43 m0;
    MtxFx43 m1;

    MTX_Scale43__from_thumb(&m0, 0x1000, top->scaleY, 0x1000);
    MTX_Scale43__from_thumb(&m1, 0x1000, bottom->scaleY, 0x1000);

    m0._30 = top->pos.x;
    m0._31 = top->pos.y;
    m0._32 = top->pos.z;
    m1._30 = bottom->pos.x;
    m1._31 = bottom->pos.y;
    m1._32 = bottom->pos.z;

    MTX_Concat43(&m0, cam, &m0);
    MTX_Concat43(&m1, cam, &m1);

    REG_GE_BEGIN = 1;               /* begin primitive (quads) */

    G3_LoadMtx43(&m0);
    REG_GE_TEXCOORD = (unsigned short)((tex->s << 8) >> 16);
    REG_GE_VTX_10 = 0x10000;
    REG_GE_TEXCOORD = 0;
    REG_GE_VTX_10 = 0xf0000;

    G3_LoadMtx43(&m1);
    REG_GE_TEXCOORD = ((unsigned short)((tex->t << 8) >> 16)) << 16;
    REG_GE_VTX_10 = 0xf0000;
    REG_GE_TEXCOORD = (unsigned short)((tex->s << 8) >> 16)
                    | (((unsigned short)((tex->t << 8) >> 16)) << 16);
    REG_GE_VTX_10 = 0x10000;

    REG_GE_END = 0;                 /* end primitive */
}
