// PURPOSE: Stores a small payload in the selected context slot.
// The second argument is probably an unused selector, while the third chooses
// a slot and the fourth supplies its flag mask.  Context mode 11 copies only
// an empty slot; other modes use the shared slot-copy helper.

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct UnkStruct_0217aa00 {
    u8 pad_000[4];
    int unk4;
    u8 pad_008[0x43d - 0x008];
    u8 slotFlags;
    u8 pad_43e[0x45c - 0x43e];
    u8 slots[1][0x5c];
} UnkStruct_0217aa00;

extern UnkStruct_0217aa00 *data_0217aa00;
extern void func_020559ec(const void *source, int slotIndex, u32 flagMask);
extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);

void func_020597d0(const void *source, int unused, int slotIndex, u32 flagMask)
{
    if (data_0217aa00->unk4 != 11) {
        func_020559ec(source, slotIndex, flagMask);
        return;
    }

    if ((data_0217aa00->slotFlags & (1 << slotIndex)) == 0) {
        Mem_CpuCopy8(source, data_0217aa00->slots[slotIndex], 0x14);
        data_0217aa00->slotFlags |= 1 << slotIndex;
    }
}
