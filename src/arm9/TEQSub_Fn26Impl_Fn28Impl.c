typedef unsigned char u8;
typedef unsigned int u32;

extern int data_0216f074;
extern void *func_0214a194(void);
extern void MI_DmaCopy16(int dmaNo, const void *src, void *dest, u32 size);
extern void CopyMemory16(const void *src, void *dest, u32 size);

void TEQSub_Fn26Impl_Fn28Impl(void *src, u32 offset, u32 size)
{
    void *base = func_0214a194();
    int dmaNo = data_0216f074;

    if (dmaNo != -1 && size > 0x1c) {
        MI_DmaCopy16(dmaNo, src, (u8 *)base + offset, size);
    } else {
        CopyMemory16(src, (u8 *)base + offset, size);
    }
}
