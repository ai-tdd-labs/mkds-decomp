// PURPOSE: Copies the first enabled transition record into the output buffer.
// The output receives a 0x14-byte record when the global transition context is active.
// A selected byte probably gates this operation, and the first flagged record is used.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct UnkStruct_0217aa00 {
    int state;
    u8 pad_004[0x84 - 4];
    u8 transitionValue;
    u8 pad_085[2];
    u8 slotFlags;
    u8 pad_088[0x454 - 0x88];
    u16 flags;
    u8 pad_456[0x45c - 0x456];
    u8 slots[1][0x22c];
} UnkStruct_0217aa00;

extern UnkStruct_0217aa00 *data_0217aa00;
extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);

int func_0204eb08(void *output)
{
    UnkStruct_0217aa00 *context;
    int result = 0;
    int enabled;
    u8 slotIndex;

    context = data_0217aa00;
    if (((context == 0) ? 0 : context->state) == 1) {
        enabled = ((context->flags & 0x40) != 0 ?
                       *((u8 *)context + 0x1699) : context->transitionValue);
    } else {
        enabled = 0;
    }

    if (enabled != 1) {
        return 0;
    }

    if (((context == 0) ? 0 : context->state) != 1) {
        return 0;
    }

    for (slotIndex = 1; slotIndex < 8; slotIndex++) {
        if ((context->slotFlags & (1 << slotIndex)) != 0) {
            Mem_CpuCopy8(context->slots[slotIndex], output, 0x14);
            result = 1;
            break;
        }
    }

    return result;
}
