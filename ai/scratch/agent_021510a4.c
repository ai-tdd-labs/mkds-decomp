// PURPOSE: Packs a StructDW record into the shared fourteen-byte output buffer.
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct StructDWRecord {
    int words[6];
} StructDWRecord;

extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);
extern u8 data_021804a0[];
extern u8 data_021804a6[];
extern u8 data_021804ac[];

void *StructDW_SomeFn_2_from_thumb(StructDWRecord *record)
{
    u64 packed;

    packed = *(u64 *)&record->words[2];
    Mem_CpuCopy8(record, data_021804a0, 5);

    data_021804a0[5] = ((record->words[1] >> 8) & 7) |
                       (((u32)packed & 0x1f) << 3);

    packed >>= 5;
    Mem_CpuCopy8(&packed, data_021804a6, 4);

    data_021804a0[10] = ((u32)(packed >> 32) & 0x3f) |
                        ((record->words[4] & 3) << 6);
    data_021804a0[11] = record->words[4] >> 2;
    Mem_CpuCopy8((u8 *)record + 0x12, data_021804ac, 2);

    return data_021804a0;
}
