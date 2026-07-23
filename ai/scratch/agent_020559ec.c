/* PURPOSE: Copies a 20-byte payload into a selected context slot.
 * The first argument is the payload source, the second selects a 0x22c-byte
 * slot, and the third masks the context's existing slot flags.
 * The selected slot is marked active after the copy.
 */

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct UnkStruct_0217aa00 {
    u8 pad000[0x43d];
    u8 slotFlags;
    u8 pad43e[0x45c - 0x43e];
    u8 slots[1][0x22c];
} UnkStruct_0217aa00;

extern UnkStruct_0217aa00 *data_0217aa00;
extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);

void func_020559ec(const void *source, int slotIndex, u32 flagMask) {
    UnkStruct_0217aa00 *context = data_0217aa00;
    u8 preservedFlags = context->slotFlags & flagMask;

    Mem_CpuCopy8(source, context->slots[slotIndex], 0x14);
    data_0217aa00->slotFlags = preservedFlags | (1 << slotIndex);
}
