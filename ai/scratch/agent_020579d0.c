// PURPOSE: Saves a personal ghost into the selected save slot.
// The slot number selects a 0xe00-byte save section and source provides its data.
// When save data is available, the function probably marks and writes that section.

typedef unsigned int u32;

typedef struct SaveDataHolder {
    unsigned char pad_00[0x0c];
    void *saveData;
    unsigned char pad_10[0x50];
    void *personalGhost;
} SaveDataHolder;

extern SaveDataHolder *data_021759d4;
extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);
extern void SV_MaybeCompressWriteNoFlagsBC_from_thumb(u32 offset,
                                                       void *data, u32 size,
                                                       u32 flag);

void WriteSaveDataSection_PersonalGhost_from_thumb(int slot, void *source)
{
    u32 offset = slot * 0xe00;
    void *destination;

    destination = data_021759d4->personalGhost;

    if (data_021759d4->saveData != 0) {
        Mem_CpuCopy8(source, destination, 0xe00);
        *(u32 *)destination = 0x47504b4e;
        SV_MaybeCompressWriteNoFlagsBC_from_thumb(offset + 0xaf00,
                                                   destination,
                                                   0xe00, 0);
    }
}
