// PURPOSE: Saves a downloaded ghost into the selected save slot.

typedef unsigned int u32;

typedef struct SaveDataHolder {
    unsigned char pad_00[0x0c];
    void *saveData;
    unsigned char pad_10[0x50];
    void *downloadGhost;
} SaveDataHolder;

extern SaveDataHolder *data_021759d4;
extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);
extern void SV_MaybeCompressWriteNoFlagsBC_from_thumb(u32 offset,
                                                       void *data, u32 size,
                                                       u32 flag);

void WriteSaveDataSection_DownloadGhost_from_thumb(int slot, void *source)
{
    u32 offset = (u32)slot << 12;
    SaveDataHolder *holder = data_021759d4;
    void *destination = holder->downloadGhost;

    if (holder->saveData != 0) {
        Mem_CpuCopy8(source, destination, 0x1000);
        *(u32 *)destination = 0x47444b4e;
        SV_MaybeCompressWriteNoFlagsBC_from_thumb(offset + 0x26f00,
                                                   destination, 0x1000, 0);
    }
}
