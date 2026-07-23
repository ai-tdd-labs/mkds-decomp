// PURPOSE: Builds a rotation matrix from three Euler angles.
// rotation supplies the X, Y and Z angles in the game's fixed angle format.
// dst receives the three axis rotations concatenated in X-Y-Z order.

typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef signed long long s64;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} VecFx32;

typedef struct {
    s32 m[9];
} MtxFx33;

extern s16 data_0215d4b4[];
extern void MTX_RotX33__from_thumb(MtxFx33 *dst, s16 sinv, s16 cosv);
extern void MTX_RotY33__from_thumb(MtxFx33 *dst, s16 sinv, s16 cosv);
extern void MTX_RotZ33__from_thumb(MtxFx33 *dst, s16 sinv, s16 cosv);
extern void MTX_Concat33(const MtxFx33 *left, const MtxFx33 *right,
                         MtxFx33 *dst);

#define ANGLE_TO_INDEX(angle)                                                \
    ((u16)((((s64)(angle) * 0xb60b60b60bLL) + 0x80000000000LL) >> 44))

void func_020d6df0(const VecFx32 *rotation, MtxFx33 *dst)
{
    MtxFx33 temp;
    u16 x = ANGLE_TO_INDEX(rotation->x);
    u16 y = ANGLE_TO_INDEX(rotation->y);
    u16 z = ANGLE_TO_INDEX(rotation->z);

    MTX_RotX33__from_thumb(dst,
                           data_0215d4b4[(x >> 4) * 2],
                           data_0215d4b4[(x >> 4) * 2 + 1]);

    MTX_RotY33__from_thumb(&temp,
                           data_0215d4b4[(y >> 4) * 2],
                           data_0215d4b4[(y >> 4) * 2 + 1]);
    MTX_Concat33(dst, &temp, dst);

    MTX_RotZ33__from_thumb(&temp,
                           data_0215d4b4[(z >> 4) * 2],
                           data_0215d4b4[(z >> 4) * 2 + 1]);
    MTX_Concat33(dst, &temp, dst);
}
