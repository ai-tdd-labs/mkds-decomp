typedef int fx32;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct GraphicsState {
    unsigned char pad_00[0xfc];
    unsigned int flags_fc;
} GraphicsState;

#pragma optimize_for_size on

extern VecFx32 data_021704dc;
extern VecFx32 data_021704e8;
extern VecFx32 data_021704f4;
extern int data_021702e8;
extern GraphicsState data_0217029c;

extern void G3i_LookAt_(const VecFx32 *pos, const VecFx32 *up,
                         const VecFx32 *target, int arg3, void *mtx);

void func_02076bcc(int *settings)
{
    // PURPOSE: Updates the graphics look-at matrix from the supplied camera vectors.
    VecFx32 *position = (VecFx32 *)(settings + 0x9c / 4);

    data_021704dc = *position;
    data_021704e8 = *(VecFx32 *)settings;
    data_021704f4 = *(VecFx32 *)(settings + 0x90 / 4);
    G3i_LookAt_(position, (VecFx32 *)settings,
                (VecFx32 *)(settings + 0x90 / 4), 0, &data_021702e8);
    data_0217029c.flags_fc &= ~0xe8;
}
