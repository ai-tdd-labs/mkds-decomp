// PURPOSE: Uploads the staff roll's object graphics to OAM.
// The shared staff-roll object probably contains its OAM entries at offset 0x10.
// It refreshes those entries and changes brightness at two specific credit frames.

typedef unsigned int u32;

typedef struct EndingStaffRollObjectData {
    int frame_count;
    char padding[0xC];
    char oam[0x400];
} EndingStaffRollObjectData;

extern EndingStaffRollObjectData *data_0217b4ac;

extern void Arm_FlushRange(void *buffer, u32 size);
extern void CopyToOamA(void *source, u32 offset, u32 size);
extern void BrightCtx_SomeFn_0(int a0, int a1);
extern void BrightCtx_SomeFn_1(int a0, int a1);

void LoadStaffRollDataOam(void)
{
    Arm_FlushRange(data_0217b4ac->oam, 0x400);
    CopyToOamA(data_0217b4ac->oam, 0, 0x400);

    if (data_0217b4ac->frame_count == 0x1A4) {
        BrightCtx_SomeFn_0(0x78, 1);
    } else if (data_0217b4ac->frame_count == 0x77A) {
        BrightCtx_SomeFn_1(0x78, 1);
    }
}
