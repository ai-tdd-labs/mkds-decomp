// PURPOSE: Writes Mission Run records into the save data section.
// The source buffer is copied into active save storage before its section is
// scheduled for writing. The stored section tag and offsets are probably part
// of the internal save-write format.

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

void WriteSaveDataSection_MissionRun_from_thumb(const void *source)
{
    void *storage = data_021759d4->saveStorage;

    if (data_021759d4->saveData != 0) {
        Mem_CpuCopy8(source, storage, 0x100);
        *(u32 *)storage = 0x524d4b4e;
        SV_MaybeCompressWriteTwoOffsetsFlagC_from_thumb(
            0x1e00, 0x32d00, (int)storage, 0x100, 0, 0);
    }
}
