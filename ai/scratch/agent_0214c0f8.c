// PURPOSE: Copies palette data to the bottom screen palette memory.
// The caller supplies source data, a destination offset, and its byte size.
// Large copies use DMA when a channel is available; small copies use the CPU.
typedef unsigned int u32;

extern int data_0216f074;
extern void MI_DmaCopy16(int dmaNo, const void *src, void *dest, u32 size);
extern void CopyMemory16(const void *src, void *dest, u32 size);

void CopyPaletteBottom(const void *src, u32 offset, u32 size)
{
    int dmaNo = data_0216f074;

    if (dmaNo != -1 && size > 0x1c) {
        MI_DmaCopy16(dmaNo, src, (void *)(offset - 0x400), size);
    } else {
        CopyMemory16(src, (void *)(offset - 0x400), size);
    }
}
