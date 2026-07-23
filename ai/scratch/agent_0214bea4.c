// PURPOSE: Copies data to the sub-screen background memory.
// The caller provides the source, destination offset, and byte count.
// Large copies use DMA when a channel is available; smaller copies use the CPU.
typedef unsigned int u32;

extern int data_0216f074;
extern void MI_DmaCopy32(int dmaNo, const void *src, void *dest, u32 size);
extern void Mem_CpuCopy32(const void *src, void *dest, u32 size);

void TEQSub_Fn35Impl(void *src, u32 offset, u32 size)
{
    int dmaNo = data_0216f074;

    if (dmaNo != -1 && size > 0x30) {
        MI_DmaCopy32(dmaNo, src, (void *)(0x06600000 + offset), size);
    } else {
        Mem_CpuCopy32(src, (void *)(0x06600000 + offset), size);
    }
}
