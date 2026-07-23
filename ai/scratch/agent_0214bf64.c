// PURPOSE: Copies data to sub-screen OAM memory.
// The caller provides a source, destination offset, and byte count.
// Large transfers use DMA when a channel is available; smaller ones use the CPU.
typedef unsigned int u32;

extern int data_0216f074;
extern void MI_DmaCopy32(int dmaNo, const void *src, void *dest, u32 size);
extern void Mem_CpuCopy32(const void *src, void *dest, u32 size);

void CopyToOamB(void *src, u32 offset, u32 size)
{
    int dmaNo = data_0216f074;

    if (dmaNo != -1 && size > 0x30) {
        MI_DmaCopy32(dmaNo, src, (void *)(offset + 0x07000400), size);
    } else {
        Mem_CpuCopy32(src, (void *)(offset + 0x07000400), size);
    }
}
