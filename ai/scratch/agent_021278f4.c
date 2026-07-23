// PURPOSE: Updates the choice screen blending during vertical blank.
// This function takes no arguments and runs only while the choice scene is active.
// It probably toggles a sub-screen blend bit from the current scene state.

typedef signed short s16;
typedef unsigned int u32;
typedef unsigned short u16;

typedef struct SelectChoisesContext {
    int unk_00;
    int unk_04;
    unsigned char unk_08[0x89c];
    int unk_8a4;
} SelectChoisesContext;

extern SelectChoisesContext *data_0217d3f4;

extern void UpdateBldcntBldalphaBldy(volatile u16 *blendRegisters,
                                     s16 firstTargetPixels,
                                     s16 secondTargetPixels,
                                     s16 evaCoefficient,
                                     s16 evbCoefficient,
                                     int brightnessCoefficient);

void SelectChoisesContext_OnSceneVblank_from_thumb(void)
{
    if (data_0217d3f4->unk_00 != 0) {
        *(volatile u32 *)0x04001010 = 0;

        if (data_0217d3f4->unk_04 != 0) {
            if (data_0217d3f4->unk_8a4 != 0) {
                goto blend_enabled;
            }
        }

        UpdateBldcntBldalphaBldy((volatile u16 *)0x04001050,
                                 30, 31, 6, 10, 0);
        *(volatile u32 *)0x04001000 =
            (*(volatile u32 *)0x04001000 & 0xffffe0ff) |
            (((*(volatile u32 *)0x04001000 & 0x00001f00) >> 8 & ~1) << 8);
        return;

blend_enabled:
        UpdateBldcntBldalphaBldy((volatile u16 *)0x04001050,
                                 30, 31, 6, 10, -10);
        *(volatile u32 *)0x04001000 =
            (*(volatile u32 *)0x04001000 & 0xffffe0ff) |
            (((*(volatile u32 *)0x04001000 & 0x00001f00) >> 8 | 1) << 8);
    }
}
