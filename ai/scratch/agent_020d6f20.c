// PURPOSE: Rotates a vector around the Y axis using an angle.
// The first argument is the source vector and the third receives the result.
// It probably uses the game's fixed-point sine and cosine table.

typedef signed short s16;
typedef signed int fx32;

typedef struct {
    fx32 m[9];
} MtxFx33;

extern s16 data_0215d4b4[];
extern void MTX_RotY33__from_thumb(MtxFx33 *mtx, s16 sinv, s16 cosv);
extern void MTX_MultVec33(void *dst, const MtxFx33 *mtx, const void *src);

void func_020d6f20(void *dst, int angle, const void *src)
{
    MtxFx33 mtx;

    angle = angle >> 4;
    MTX_RotY33__from_thumb(&mtx, data_0215d4b4[angle * 2], data_0215d4b4[angle * 2 + 1]);
    MTX_MultVec33(dst, &mtx, src);
}
