// PURPOSE: Applies the text system's display settings during vertical blank.
// This function takes no arguments and does nothing while the context is inactive.
// It copies the stored background offsets and updates blending for both screens.
// The exact meanings of the individual blend fields are uncertain.

typedef unsigned int u32;
typedef unsigned short u16;

typedef struct TextSystemContext {
    unsigned char padding_00[0x50];
    int active;
} TextSystemContext;

extern TextSystemContext *data_0217d3f0;

extern void UpdateBldcntBldalphaBldy(volatile u16 *blendRegisters,
                                     int firstTargetPixels,
                                     int secondTargetPixels,
                                     int evaCoefficient,
                                     int evbCoefficient,
                                     int brightnessCoefficient);

/* Keep these raw context offsets as pointer literals for the Thumb pool. */
#define TEXT_FIELD(context, offset) \
    (*(int *)((char *)(offset) + (u32)(context)))

void TextSystemContext_OnSceneVblank_from_thumb(void)
{
    if (data_0217d3f0->active != 0) {
        *(volatile u32 *)0x04000018 =
            ((u32)TEXT_FIELD(data_0217d3f0, 0x54) << 16) & 0x01ff0000;
        *(volatile u32 *)0x04001010 =
            ((u32)TEXT_FIELD(data_0217d3f0, 0x58) << 16) & 0x01ff0000;

        if (TEXT_FIELD(data_0217d3f0, 0x6c) != 0) {
            UpdateBldcntBldalphaBldy(
                (volatile u16 *)0x04000050,
                TEXT_FIELD(data_0217d3f0, 0x80),
                0x1f,
                TEXT_FIELD(data_0217d3f0, 0x88),
                TEXT_FIELD(data_0217d3f0, 0x90),
                TEXT_FIELD(data_0217d3f0, 0x7c));
        } else {
            UpdateBldcntBldalphaBldy(
                (volatile u16 *)0x04000050,
                0,
                0x1f,
                TEXT_FIELD(data_0217d3f0, 0x88),
                TEXT_FIELD(data_0217d3f0, 0x90),
                TEXT_FIELD(data_0217d3f0, 0x7c));
        }

        if (TEXT_FIELD(data_0217d3f0, 0x70) != 0) {
            UpdateBldcntBldalphaBldy(
                (volatile u16 *)0x04001050,
                TEXT_FIELD(data_0217d3f0, 0x84),
                0x1f,
                TEXT_FIELD(data_0217d3f0, 0x8c),
                TEXT_FIELD(data_0217d3f0, 0x94),
                TEXT_FIELD(data_0217d3f0, 0x7c));
            return;
        }

        UpdateBldcntBldalphaBldy(
            (volatile u16 *)0x04001050,
            0,
            0x1f,
            TEXT_FIELD(data_0217d3f0, 0x8c),
            TEXT_FIELD(data_0217d3f0, 0x94),
            TEXT_FIELD(data_0217d3f0, 0x7c));
    }
}
