// PURPOSE: Transfers a game card block and starts its ROM command.
// The card state is stored at data_0217fa40, probably as a DMA source and command.
// It copies 0x200 bytes to the card DMA register, then sends the encoded command.
// Finally it mirrors a card status word to the card control register.

typedef unsigned int u32;

#pragma optimize_for_size on

typedef struct {
    char pad00[0x1c];
    u32 command;
    u32 destination;
    u32 unused24;
    u32 dma;
} CardTransferState;

extern CardTransferState data_0217fa40;
extern u32 data_02180080[];

extern void MIi_CardDmaCopy32(u32 dmaNo, const void *src, void *dest, u32 size);
extern void Card_WriteRomOperation(u32 command0, u32 command1);

void MaybeGamecardTransferSY(void)
{
    CardTransferState *const state = &data_0217fa40;

    MIi_CardDmaCopy32(state->dma,
                      (const void *)0x04100010,
                      (void *)state->destination,
                      0x200);
    Card_WriteRomOperation((state->command >> 8) | 0xb7000000,
                           state->command << 24);
    *(volatile u32 *)0x040001a4 = data_02180080[1];
}
