// PURPOSE: Formats the current multiplayer network error code.
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct MultiplayErrorWork {
    unsigned char unknown_00[8];
    void *messageBuffer;
} MultiplayErrorWork;

extern MultiplayErrorWork *data_0217d408;

extern void Mem_CpuFill16(u16 value, void *destination, u32 size);
extern u32 GetMaybeNetErrorCode(void);
extern void FormatIntegerInString16_from_thumb(u32 value, u16 *destination);
extern void MaybeHandleBmgFormatting_from_thumb(u16 *source, void *destination,
                                                 void *buffer, u32 bufferSize);

void MaybeFormatMultiplayNetErrorCode_from_thumb(void)
{
    volatile u16 fill;
    u16 errorText[10];

    fill = 0;
    Mem_CpuFill16(fill, errorText, 0x14);
    FormatIntegerInString16_from_thumb(GetMaybeNetErrorCode(), errorText);
    MaybeHandleBmgFormatting_from_thumb(errorText, data_0217d408->messageBuffer,
                                        (unsigned char *)data_0217d408 + 0x1444,
                                        0x600);
    data_0217d408->messageBuffer = (unsigned char *)data_0217d408 + 0x1444;
}
