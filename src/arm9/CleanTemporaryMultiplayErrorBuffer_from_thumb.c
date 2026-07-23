// PURPOSE: Clears the temporary multiplayer error buffer.
typedef unsigned short u16;
typedef unsigned int u32;

extern void *data_0217d408;
extern void Mem_CpuFill16(u16 value, void *destination, u32 size);

void CleanTemporaryMultiplayErrorBuffer_from_thumb(void)
{
    volatile u16 fill;

    fill = 0;
    Mem_CpuFill16(fill, (unsigned char *)data_0217d408 + 0x1444, 0x600);
}
