typedef unsigned short u16;
typedef unsigned int u32;

typedef struct UnkStruct_0217aa00 UnkStruct_0217aa00;

extern UnkStruct_0217aa00 *data_0217aa00;
extern void *Mem_AllocateHeapAligned(void *heap, u32 size, int alignment);
extern void DecompressLzss(const void *source, void *destination);

void func_0204f770(void)
{
    // PURPOSE: Loads and decompresses the selected resource into its buffer.
    int offset;
    u32 size;
    void *buffer;

    offset = (int)(short)(*(u16 *)((char *)data_0217aa00 + 0x432) - 1) * 0x88;
    size = *(u32 *)*(void **)((char *)data_0217aa00 + offset + 0x1714) >> 8;
    buffer = *(void **)((char *)data_0217aa00 + offset + 0x1718);
    if (buffer == 0) {
        buffer = Mem_AllocateHeapAligned(
            *(void **)((char *)data_0217aa00 + offset + 0x1720), size, 0x20);
        *(void **)*(void **)((char *)data_0217aa00 + offset + 0x171c) = buffer;
    }
    DecompressLzss(*(void **)((char *)data_0217aa00 + offset + 0x1714), buffer);
    *(u32 *)((char *)data_0217aa00 + offset + 0x1720) &= 0xdfffffff;
}
