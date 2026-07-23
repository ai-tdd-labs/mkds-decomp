// PURPOSE: Counts valid saved online information records.
typedef unsigned char u8;
typedef unsigned int u32;

typedef struct OnlineInfo {
    u8 data[0x22];
    u8 valid : 1;
    u8 remainingFlags : 7;
    u8 trailingByte;
} OnlineInfo;

typedef struct OnlineInfoTable {
    u32 unknown0;
    OnlineInfo records[];
} OnlineInfoTable;

typedef struct SaveDataHolder {
    u8 padding[0x20];
    OnlineInfoTable *onlineInfo;
} SaveDataHolder;

extern SaveDataHolder *data_0217aa08;
extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);

int func_0205e548(void)
{
    u8 count = 0;
    u8 index = count;
    OnlineInfo *output = 0;

    for (; index < 0x3c; index++) {
        if (output != 0) {
            Mem_CpuCopy8(&data_0217aa08->onlineInfo->records[index], output,
                         0x24);
        }
        if (data_0217aa08->onlineInfo->records[index].valid != 0) {
            count++;
        }
    }

    return count;
}
