// PURPOSE: Queues resource data in the first available shared slot.
// The source descriptor is copied into one of twelve entries.
// The heap, output pointer, and option bits are saved for later loading.
// The final argument probably selects a shared source pointer.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct ResourceSlotFlags {
    u32 options : 29;
    u32 usesSharedSource : 1;
    u32 pending : 1;
    u32 unknown : 1;
} ResourceSlotFlags;

typedef struct ResourceSlot {
    u8 pad_00[0x34];
    u8 descriptor[0x40];
    void *source;
    void *buffer;
    void **output;
    void *heap;
    ResourceSlotFlags flags;
} ResourceSlot;

typedef struct UnkStruct_0217aa00 {
    u8 pad_0000[0x16a0];
    ResourceSlot slots[12];
    u8 pad_1d00[0x58];
    void *sharedSource;
} UnkStruct_0217aa00;

extern UnkStruct_0217aa00 *data_0217aa00;
extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);

void func_0204f4d0(void *source, void *heap, void **output, u32 options,
                   int useSharedSource)
{
    u16 i = 0;
    UnkStruct_0217aa00 *state = data_0217aa00;

    for (; i < 12; i++) {
        if (state->slots[i].descriptor[0] == 0) {
            Mem_CpuCopy8(source, state->slots[i].descriptor, 0x40);

            if (useSharedSource != 0) {
                data_0217aa00->slots[i].source =
                    data_0217aa00->sharedSource;
                data_0217aa00->slots[i].buffer = 0;
                data_0217aa00->slots[i].flags.usesSharedSource = 1;
                data_0217aa00->slots[i].flags.options = options;
            } else {
                data_0217aa00->slots[i].source = 0;
                data_0217aa00->slots[i].buffer = 0;
                data_0217aa00->slots[i].flags.usesSharedSource = 0;
                data_0217aa00->slots[i].flags.options = options;
            }

            data_0217aa00->slots[i].heap = heap;
            data_0217aa00->slots[i].flags.pending = 1;
            data_0217aa00->slots[i].output = output;
            return;
        }
    }
}
