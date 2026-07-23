// PURPOSE: Initializes a data block and copies a small generated record into it.
// Clears the probably 0x400-byte block, marks one byte in each of three sections,
// then obtains a temporary record and copies its first fourteen bytes twice.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u32 words[6];
} StructDWRecord;

extern void Mem_CpuFill16(u16 value, void *destination, u32 size);
extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);
extern void StructDW_SomeFn_from_thumb(StructDWRecord *record);
extern void *StructDW_SomeFn_2_from_thumb(StructDWRecord *record);

int StructDC_SomeFn_from_thumb(u8 *destination)
{
    volatile u16 fill;
    StructDWRecord record;
    void *source;
    int i;
    u8 *section;

    fill = 0;
    Mem_CpuFill16(fill, destination, 0x400);

    section = destination;
    for (i = 0; i < 3; i++) {
        section[0xe7] = 0xff;
        section += 0x100;
    }

    StructDW_SomeFn_from_thumb(&record);
    source = StructDW_SomeFn_2_from_thumb(&record);

    for (i = 0; i < 2; i++) {
        Mem_CpuCopy8(source, destination + 0xf0, 0xe);
        destination += 0x100;
    }

    return 0;
}
