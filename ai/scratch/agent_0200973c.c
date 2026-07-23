/* PURPOSE: Copies a complete slot update into a player entry.
 * The destination receives 15 packed slots from sourceData and records how
 * many bits are set in sourceMask, including the always-valid header bit.
 * updateMask is probably the set of slots changed by this update.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct PlayerSlotEntry {
    u8 pad0[0x358];
    u8 validPartCount;
    u8 pad359;
    u16 validPartMask;
    u16 updateMask;
    u8 slotData[0x14a];
    u8 pad4a8[0xc];
    u8 generation;
} PlayerSlotEntry;

extern void CopyMemory16(const void *source, void *destination, u32 size);

void func_0200973c(PlayerSlotEntry *entry, const void *sourceData,
                   u16 sourceMask, u16 updateMask)
{
    u8 validPartCount = 1;
    int slot;

    CopyMemory16(sourceData, entry->slotData, 0x14a);

    for (slot = 0; slot < 15; slot++) {
        if (sourceMask & (2 << slot)) {
            validPartCount++;
        }
    }

    entry->validPartCount = validPartCount;
    sourceMask |= 1;
    entry->validPartMask = sourceMask;
    entry->updateMask = updateMask;
    entry->generation++;
}
