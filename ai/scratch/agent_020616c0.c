/* PURPOSE: Copies a valid 20-byte record into an output buffer.
 * The first argument is probably one entry in a 0x30-byte record table, and
 * the second argument receives its payload. Returns 0 when the entry's valid
 * bit is clear; otherwise copies the payload and returns 1.
 */

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct RecordEntry {
    u32 unknown0;
    u32 packedValue;
    u32 valid : 1;
    u32 unknownFlags : 31;
    u8 payload[0x14];
} RecordEntry;

extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);

int func_020616c0(RecordEntry *entry, void *output) {
    if (entry->valid != 1) {
        return 0;
    }

    Mem_CpuCopy8(entry->payload, output, 0x14);
    return 1;
}
