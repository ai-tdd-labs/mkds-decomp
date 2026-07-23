typedef unsigned char u8;
typedef unsigned int u32;

extern int data_0216f074;
extern void *GetVramBg2BaseOffset_Bottom(void);
extern void MI_DmaCopy32(int dmaNo, const void *src, void *dest, u32 size);
extern void Mem_CpuCopy32(const void *src, void *dest, u32 size);

void CopyBgData_Bg2_Bottom(void *src, u32 offset, u32 size)
{
    void *base = GetVramBg2BaseOffset_Bottom();
    int dmaNo = data_0216f074;

    if (dmaNo != -1 && size > 0x30) {
        MI_DmaCopy32(dmaNo, src, (u8 *)base + offset, size);
    } else {
        Mem_CpuCopy32(src, (u8 *)base + offset, size);
    }
}
