typedef unsigned char u8;
typedef unsigned int u32;

typedef struct SaveDataHolder {
    u8 pad_00[0x0c];
    void *saveData;
    u8 pad_10[0x50];
    void *saveStorage;
} SaveDataHolder;

extern SaveDataHolder *data_021759d4;
extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);
extern void SV_MaybeCompressWriteTwoOffsetsFlagC_from_thumb(int a, int b,
                                                            int c, int d,
                                                            int e, int f);

// PURPOSE: Writes the save header into its save data section.
void WriteSaveDataSection_Header_from_thumb(const void *source)
{
    void *storage = data_021759d4->saveStorage;

    if (data_021759d4->saveData != 0) {
        Mem_CpuCopy8(source, storage, 0x100);
        *(u32 *)storage = 0x53444b4d;
        *(u32 *)((u8 *)storage + 4) = 0x30315653;
        *(u32 *)((u8 *)storage + 8) = 0x59534b4e;
        SV_MaybeCompressWriteTwoOffsetsFlagC_from_thumb(
            0, 0x30f00, (int)storage, 0x100, 0, 1);
    }
}
