// PURPOSE: Writes an NKFE save section into the selected save slot.

typedef unsigned int u32;

struct SaveDataHolder {
    unsigned char unk_00[0x0c];
    int operationActive;
    unsigned char unk_10[0x50];
    void *saveBuffer;
};

extern struct SaveDataHolder *data_021759d4;
extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);
extern void SV_MaybeCompressWriteTwoOffsetsFlagC_from_thumb(
    u32 sectionOffset, u32 saveOffset, void *destination, u32 size,
    int flagA, int flagB);

void WriteSaveDataSection_NKFE_from_thumb(const void *source, int slot)
{
    u32 offset = slot * 0xb00;
    struct SaveDataHolder *holder = data_021759d4;
    void *saveBuffer = holder->saveBuffer;

    if (holder->operationActive != 0) {
        Mem_CpuCopy8(source, saveBuffer, 0xb00);
        *(u32 *)saveBuffer = 0x45464b4e;
        SV_MaybeCompressWriteTwoOffsetsFlagC_from_thumb(
            offset + 0x2b00, offset + 0x33a00,
            saveBuffer, 0xb00, 0, 0);
    }
}
