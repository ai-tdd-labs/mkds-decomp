// PURPOSE: Starts an asynchronous game card read with DMA when the transfer is safe.
// The card state supplies the ROM source, RAM destination, length, and DMA channel.
// Transfers touching TCM or using unsuitable alignment fall back to another path.
// The output receives the card control flags before DMA is started.

typedef unsigned int u32;

typedef struct CardTransferState {
    unsigned char pad00[0x1c];
    u32 source;
    u32 destination;
    u32 length;
    u32 dmaChannel;
} CardTransferState;

typedef struct CardRomState {
    void *readFunction;
    u32 control;
} CardRomState;

extern CardTransferState data_0217fa40;

extern u32 GetDtcmStartAddress(void);
extern u32 Os_DisableIrq(void);
extern void IC_InvalidateRangeNoClean(void *start, u32 length);
extern void DC_SomeClean(void *start, u32 length);
extern void DC_InvalidateRangeNoClean(void *start, u32 length);
extern void Mem_DcDrainWriteBuffer(void);
extern void Os_SetIrqHandler(u32 mask, void (*handler)(void));
extern u32 SetIF(u32 mask);
extern u32 Os_EnableIrqHandler(u32 mask);
extern void Os_RestoreIrq(u32 state);
extern void CardIRQHandler(void);
extern void MaybeGamecardTransferSY(void);

static inline int Card_IsInTcm(u32 buffer, u32 length)
{
    const u32 itcm = 0x01ff8000;
    const u32 dtcm = GetDtcmStartAddress();

    return ((itcm < buffer + length) && (itcm + 0x8000 > buffer)) ||
           ((dtcm < buffer + length) && (dtcm + 0x4000 > buffer));
}

static inline u32 Card_GetReadControl(void)
{
    const u32 control = *(volatile u32 *)0x027ffe60;

    return (control & ~0x07000000) | 0xa1000000;
}

int StructSZ_SomeFn(CardRomState *romState)
{
    CardTransferState *const state = &data_0217fa40;
    const u32 destination = state->destination;
    u32 length = state->length;
    const int isAsync = !(destination & 3) &&
                        (state->dmaChannel <= 3) &&
                        !Card_IsInTcm(destination, length) &&
                        !((state->source | length) & 0x1ff) &&
                        (length > 0);

    romState->control = Card_GetReadControl();

    if (isAsync) {
        u32 irqState = Os_DisableIrq();

        IC_InvalidateRangeNoClean((void *)destination, length);
        {
            u32 position = destination;
            u32 misalignment = destination & 0x1f;

            if (misalignment) {
                position -= misalignment;
                DC_SomeClean((void *)position, 0x20);
                DC_SomeClean((void *)(position + length), 0x20);
                length += 0x20;
            }

            DC_InvalidateRangeNoClean((void *)position, length);
            Mem_DcDrainWriteBuffer();
        }

        Os_SetIrqHandler(0x80000, CardIRQHandler);
        (void)SetIF(0x80000);
        (void)Os_EnableIrqHandler(0x80000);
        Os_RestoreIrq(irqState);
        MaybeGamecardTransferSY();
    }

    return isAsync;
}
