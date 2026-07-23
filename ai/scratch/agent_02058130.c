// PURPOSE: Copies a saved value into the active context slot.
// Takes no arguments. It probably selects slot zero normally and a saved
// slot index while the context is in state 2, then copies four bytes there.
// It also clears a transfer-status byte and marks the copied data as ready.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct UnkStruct_0217aa00 {
    u32 state;
    u8 unknown_004[0x432 - 0x004];
    u16 activeSlot;
    u8 unknown_434[0x680 - 0x434];
    u8 slots[7][0x22c];
    u8 unknown_15b4[0x162a - 0x15b4];
    u8 dataReadyFlags;
    u8 unknown_162b[0x164d - 0x162b];
    u8 transferStatus;
} UnkStruct_0217aa00;

typedef struct SaveDataHolder {
    u8 *primaryData;
} SaveDataHolder;

extern UnkStruct_0217aa00 *data_0217aa00;
extern SaveDataHolder *data_0217aa08;
extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);

void func_02058130(void)
{
    u16 slotIndex = 0;
    UnkStruct_0217aa00 *context;

    data_0217aa00->transferStatus = 0;
    context = data_0217aa00;

    if (context->state == 2) {
        slotIndex = context->activeSlot;
    }

    Mem_CpuCopy8(data_0217aa08->primaryData + 0x20,
                 context->slots[slotIndex], 4);
    data_0217aa00->dataReadyFlags |= 1;
}
