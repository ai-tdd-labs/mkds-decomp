// PURPOSE: Prepares the text graphics and sound for a new text sequence.
// This function takes no arguments and updates the shared text context.
// It promotes queued channels, rebuilds the tile maps, and queues graphics.
// It probably starts the sequence sound when both channels are idle.

#pragma optimize_for_size on

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct TextGraphicSize {
    u8 width;
    u8 height;
} TextGraphicSize;

extern u8 *data_0217d3f0;
extern TextGraphicSize data_0215d044[];
extern u16 data_0215d054[];
extern u8 data_0217d068[];

extern void TextSystemContext_LoadEnabledSpritesAndAnimations_from_thumb(
    int *enabledGraphics);
extern void AllocateReserveTEQSub(
    int command, int offset, void *destination, int size);
extern void TextSystemContext_ReloadButtonGraphics_from_thumb(void);
extern void NNSi_MaybeSndPlayerStartSeq(
    void *player, int playerNo, int sequenceId);

void TextSystemContext_UpdateFn_State0_from_thumb(void)
{
    int enabledGraphics[9];
    int i;
    int byteOffset;
    int *enabledGraphic;
    register u8 **global = &data_0217d3f0;

    if (*(int *)(*global + 0x34) == 0) {
        return;
    }

    i = 0;
    byteOffset = i;
    enabledGraphic = enabledGraphics;

    volatile int inactiveGraphic = 0;
    volatile int clearQueuedGraphic = 0;

    do {
        if (i <= 6) {
            if (*(int *)(*global + byteOffset + 0x2204) != 0) {
                *enabledGraphic = 1;
            } else {
                *enabledGraphic = 0;
            }
        } else if (*(int *)(*global + byteOffset + 4) != 0) {
            /* Promote the queued entry into its active slot. */
            *(int *)(*global + byteOffset + 4) = clearQueuedGraphic;
            *(int *)(*global + byteOffset - 4) = 1;
            *enabledGraphic = 1;
        } else {
            *enabledGraphic = inactiveGraphic;
        }

        byteOffset += 4;
        enabledGraphic++;
        i++;
    } while (i < 9);

    TextSystemContext_LoadEnabledSpritesAndAnimations_from_thumb(
        enabledGraphics);

    AllocateReserveTEQSub(0x0a, 0, data_0217d3f0 + 0x54, 0x1000);
    AllocateReserveTEQSub(0x18, 0, data_0217d3f0 + 0x1054, 0x1000);

    *(int *)(data_0217d3f0 + 4) = 1;
    *(int *)(data_0217d3f0 + 0x0c) = 0;

    for (i = 0, byteOffset = 0; i < 2; i++, byteOffset += 4) {
        *(int *)(data_0217d3f0 + byteOffset + 0x205c) =
            *(int *)(data_0217d3f0 + byteOffset + 0x2064);
    }

    for (i = 0, byteOffset = 0; i < 2; i++, byteOffset += 4) {
        *(int *)(data_0217d3f0 + byteOffset + 0x206c) =
            *(int *)(data_0217d3f0 + byteOffset + 0x2074);
    }

    for (i = 0, byteOffset = 0; i < 7; i++, byteOffset += 4) {
        u8 *entry = data_0217d3f0 + byteOffset;

        if (*(int *)(entry + 0x2204) != 0) {
            AllocateReserveTEQSub(
                i <= 1 ? 6 : 0x14,
                (*(int *)(entry + 0x2220) + data_0215d054[i]) << 5,
                *(void **)(entry + 0x21e8),
                data_0215d044[i].width * data_0215d044[i].height << 5);
        }
    }

    if (*(int *)(data_0217d3f0 + 0x28) > 0) {
        TextSystemContext_ReloadButtonGraphics_from_thumb();
    }

    if (*(int *)(data_0217d3f0 + 0x18) == 0 &&
        *(int *)(data_0217d3f0 + 0x1c) == 0) {
        int sequenceId = *(int *)(data_0217d3f0 + 0x2258);

        if (sequenceId != -1) {
            NNSi_MaybeSndPlayerStartSeq(
                data_0217d068, 0, (u16)sequenceId);
        }
    }
}
