// PURPOSE: Copies sprite data into main OAM memory.
// The source bytes are copied to the requested offset in main-engine OAM.
// Large copies use DMA when a DMA channel is available; other copies use the CPU.

typedef unsigned char u8;
typedef unsigned int u32;

extern int data_0216f074;
extern void MI_DmaCopy32(int dmaNo, const void *src, void *dest, u32 size);
extern void Mem_CpuCopy32(const void *src, void *dest, u32 size);

void CopyToOamA(void *src, u32 offset, u32 size)
{
    int dmaNo = data_0216f074;

    if (dmaNo != -1 && size > 0x30) {
        MI_DmaCopy32(dmaNo, src, (u8 *)0x07000000 + offset, size);
    } else {
        Mem_CpuCopy32(src, (u8 *)0x07000000 + offset, size);
    }
}
