// PURPOSE: Copies tile graphics into the top screen's VRAM.
// The source bytes are written at the requested offset from 0x06400000.
// Large transfers use DMA when a DMA channel is available; smaller transfers
// or transfers without a DMA channel use the CPU copy routine.
typedef unsigned char u8;
typedef unsigned int u32;

extern int data_0216f074;
extern void MI_DmaCopy32(int dmaNo, const void *src, void *dest, u32 size);
extern void Mem_CpuCopy32(const void *src, void *dest, u32 size);

void CopyTileDataTop_0(void *src, u32 offset, u32 size)
{
    int dmaNo = data_0216f074;

    if (dmaNo != -1 && size > 0x30) {
        MI_DmaCopy32(dmaNo, src, (u8 *)0x06400000 + offset, size);
    } else {
        Mem_CpuCopy32(src, (u8 *)0x06400000 + offset, size);
    }
}
