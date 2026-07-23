// PURPOSE: Stores one saved online-information record.
// The slot selects a probably online-profile record in save data.
// The supplied record is copied into that slot.

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

void GlobalZ_SetOI(int slot, const OnlineInfo *input)
{
    Mem_CpuCopy8(input, &data_0217aa08->onlineInfo->records[slot],
                 sizeof(OnlineInfo));
}
