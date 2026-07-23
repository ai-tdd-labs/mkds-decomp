typedef unsigned char u8;
typedef unsigned int u32;

extern void Mem_CpuFill8(void *destination, int value, u32 size);
extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);
extern void func_02150808(u8 *out, u8 *msg, int msglen, u8 *key, int keylen);
extern u8 *data_02161768;
extern int data_0216176c;

int Fs_ComputeCompareDigest(u8 *expected, u8 *msg, int msglen)
{
    // PURPOSE: Computes an HMAC-SHA1 digest and compares it with an expected digest.
    u8 digest[0x14];
    u8 key[0x40];
    u32 offset;

    Mem_CpuFill8(digest, 0, 0x14);
    Mem_CpuCopy8(data_02161768, key, data_0216176c);
    func_02150808(digest, msg, msglen, key, data_0216176c);

    for (offset = 0; offset < 0x14; offset += 4) {
        if (*(u32 *)(digest + offset) != *(u32 *)(expected + offset)) {
            break;
        }
    }

    return offset == 0x14;
}
