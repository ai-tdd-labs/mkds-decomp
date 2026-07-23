typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct StructDW {
    u32 words[5];
} StructDW;

extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);
extern u8 data_021804a0[];
extern u8 data_021804a5[];
extern u8 data_021804aa[];
extern u8 data_021804ac[];

void StructDW_MaybeCreate_from_thumb(StructDW *out)
{
    // PURPOSE: Decodes the shared compact StructDW data into an output record.
    Mem_CpuCopy8(data_021804a0, out, 6);
    *(u64 *)&out->words[0] &= 0x000007FFFFFFFFFFULL;

    Mem_CpuCopy8(data_021804a5, &out->words[2], 6);
    *(u64 *)&out->words[2] >>= 3;
    *(u64 *)&out->words[2] &= 0x000003FFFFFFFFFFULL;

    Mem_CpuCopy8(data_021804aa, &out->words[4], 2);
    *(u16 *)&out->words[4] >>= 6;
    *(u16 *)&out->words[4] &= 0x3ff;

    Mem_CpuCopy8(data_021804ac, (u8 *)out + 0x12, 2);
}
