// PURPOSE: Copies a valid online record payload into an output buffer.
typedef struct OnlineInfo {
    unsigned char unknown_00[0x22];
    unsigned char status;
    unsigned char unknown_23;
    unsigned char unknown_24[4];
} OnlineInfo;

extern int GlobalZ_GetOI(int slot, OnlineInfo *output);
extern void Mem_CpuCopy8(const void *source, void *destination, unsigned int size);

int func_020608fc(int slot, void *output)
{
    volatile OnlineInfo info;

    GlobalZ_GetOI(slot, (OnlineInfo *)&info);
    if ((((unsigned int)info.status << 31) >> 31) != 1)
        return 0;

    Mem_CpuCopy8(&info.unknown_00[0x0e], output, 0x14);
    return 1;
}
