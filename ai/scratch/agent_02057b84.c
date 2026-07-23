// PURPOSE: Writes Grand Prix records into the save data section.
// The source buffer is copied into the active save storage before scheduling
// its Grand Prix section write. The exact meaning of the two zero flags is
// probably internal save-write state.

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

void WriteSaveDataSection_GrandPrix_from_thumb(const void *source)
{
    void *storage = data_021759d4->saveStorage;

    if (data_021759d4->saveData != 0) {
        Mem_CpuCopy8(source, storage, 0x400);
        *(u32 *)storage = 0x50474b4e;
        SV_MaybeCompressWriteTwoOffsetsFlagC_from_thumb(
            0x400, 0x31300, (int)storage, 0x400, 0, 0);
    }
}
