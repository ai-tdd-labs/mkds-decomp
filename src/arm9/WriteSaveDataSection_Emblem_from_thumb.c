typedef unsigned int u32;

typedef struct SaveDataHolder {
    unsigned char pad_00[0x0c];
    int operationActive;
    unsigned char pad_10[0x50];
    void *emblemBuffer;
} SaveDataHolder;

extern SaveDataHolder *data_021759d4;
extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);
extern void SV_MaybeCompressWriteTwoOffsetsFlagC_from_thumb(int a, int b,
                                                            int c, int d,
                                                            int e, int f);

// PURPOSE: Saves the emblem data into its save section.
void WriteSaveDataSection_Emblem_from_thumb(const void *source)
{
    void *emblemBuffer = data_021759d4->emblemBuffer;

    if (data_021759d4->operationActive != 0) {
        Mem_CpuCopy8(source, emblemBuffer, 0x300);
        *(u32 *)emblemBuffer = 0x4d454b4e;
        SV_MaybeCompressWriteTwoOffsetsFlagC_from_thumb(0x100, 0x31000,
                                                        (int)emblemBuffer,
                                                        0x300, 0, 0);
    }
}
