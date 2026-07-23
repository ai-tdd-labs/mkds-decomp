/*
PURPOSE: Copies graphics data into the other sub-screen background memory.
The source pointer, destination byte offset, and byte count are supplied by the caller.
Large transfers probably use DMA when a DMA channel is available; smaller transfers use the CPU.
*/
typedef unsigned char u8;
typedef unsigned int u32;

extern int data_0216f074;
extern void *func_0214a2a0(void);
extern void MI_DmaCopy16(int dmaNo, const void *src, void *dest, u32 size);
extern void CopyMemory16(const void *src, void *dest, u32 size);

void TEQSub_Fn25Impl(void *src, u32 offset, u32 size)
{
    void *backgroundBase = func_0214a2a0();
    int dmaNo = data_0216f074;

    if (dmaNo != -1 && size > 0x1c) {
        MI_DmaCopy16(dmaNo, src, (u8 *)backgroundBase + offset, size);
    } else {
        CopyMemory16(src, (u8 *)backgroundBase + offset, size);
    }
}
