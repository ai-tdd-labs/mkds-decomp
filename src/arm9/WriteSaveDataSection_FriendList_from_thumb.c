// PURPOSE: Writes the friend list into its save data section.
// The supplied friend-list buffer is copied into the active save storage.
// It probably schedules a compressed write using the friend-list section tag.

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

void WriteSaveDataSection_FriendList_from_thumb(const void *source)
{
    void *storage = data_021759d4->saveStorage;
    if (data_021759d4->saveData != 0) {
        Mem_CpuCopy8(source, storage, 0xc00);
        *(u32 *)storage = 0x4c464b4e;
        SV_MaybeCompressWriteTwoOffsetsFlagC_from_thumb(
            0x1f00, 0x32e00, (int)storage, 0xc00, 0, 0);
    }
}
