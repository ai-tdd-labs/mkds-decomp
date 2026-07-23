/* PURPOSE: Reads one saved online-information record.
 * The slot selects a probably online-profile record from the save data.
 * If output is non-null, the full 0x24-byte record is copied there.
 * The return value reports whether the record's low status bit is set.
 */

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

int GlobalZ_GetOI(int slot, OnlineInfo *output)
{
    if (output != 0) {
        Mem_CpuCopy8(&data_0217aa08->onlineInfo->records[slot], output,
                     sizeof(OnlineInfo));
    }

    /* Reload through the global because the copy may have changed save data. */
    return data_0217aa08->onlineInfo->records[slot].valid != 0;
}
