// PURPOSE: Copies a graphics block into the sub-screen memory area.
// The caller supplies the source, byte offset, and byte count.
// Large transfers use the available DMA channel; smaller ones use a CPU copy.
typedef unsigned char u8;
typedef unsigned int u32;

extern int data_0216f074;
extern void MI_DmaCopy16(int dmaNo, const void *src, void *dest, u32 size);
extern void CopyMemory16(const void *src, void *dest, u32 size);

void TEQSub_Fn30Impl(void *src, u32 offset, u32 size)
{
    if (data_0216f074 != -1 && size > 0x1c) {
        MI_DmaCopy16(data_0216f074, src, (u8 *)&data_0216f074 + offset, size);
    } else {
        CopyMemory16(src, (u8 *)&data_0216f074 + offset, size);
    }
}
