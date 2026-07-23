// PURPOSE: Copies palette data into video memory.
// The caller supplies source data, a palette-memory offset, and a byte count.
// Large transfers use an available DMA channel; smaller transfers use a CPU copy.

typedef unsigned char u8;
typedef unsigned int u32;

extern int data_0216f074;
extern void MI_DmaCopy16(int dmaNo, const void *src, void *dest, u32 size);
extern void CopyMemory16(const void *src, void *dest, u32 size);

void CopySomePaletteData(void *src, u32 offset, u32 size)
{
    if (data_0216f074 != -1 && size > 0x1c) {
        MI_DmaCopy16(data_0216f074, src, (u8 *)0x05000000 + offset, size);
    } else {
        CopyMemory16(src, (u8 *)0x05000000 + offset, size);
    }
}
