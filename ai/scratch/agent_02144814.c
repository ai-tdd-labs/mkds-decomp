// PURPOSE: Writes one flagged record into the selected transfer buffer.
/*
 * The context owns four 0x200-byte slots and tracks which records are pending.
 * A null source clears the selected record instead of copying new data into it.
 * The slot masks are updated with interrupts disabled after the write finishes.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct BufferSlot {
    u16 pendingMask;
    u16 completedMask;
    u8 data[0x1fc];
} BufferSlot;

typedef struct BufferContext {
    BufferSlot slots[4];
    u8 pad_800[8];
    u16 currentSlot;
    u8 pad_80a[4];
    u16 activeMask;
    u16 transferSize;
    u8 pad_812[6];
    u16 state;
} BufferContext;

extern u32 func_021445e0(BufferContext *context, u16 mask, void *data,
                         int bitIndex);
extern void CopyMemory16(const void *source, void *destination, u32 size);
extern void Mem_CpuFill16(u16 value, void *destination, u32 size);
extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 irq);

void func_02144814(BufferContext *context, int bitIndex, const void *source)
{
    u16 bit = (u16)(1U << bitIndex);
    u16 activeMask = context->activeMask;
    u16 slot;
    void *destination;
    u32 irq;

    if ((activeMask & bit) == 0)
        return;

    slot = context->currentSlot;
    if ((context->slots[slot].pendingMask & bit) == 0) {
        if (context->state != 1)
            return;

        slot = (u16)((slot + 1) & 3);
        if ((context->slots[slot].pendingMask & bit) == 0)
            return;
    }

    destination = (void *)func_021445e0(context, activeMask,
                                        context->slots[slot].data, bitIndex);
    if (source != 0) {
        CopyMemory16(source, destination, context->transferSize);
    } else {
        volatile u16 zero = 0;
        Mem_CpuFill16(zero, destination, context->transferSize);
    }

    irq = Os_DisableIrq();
    context->slots[slot].pendingMask &= ~bit;
    context->slots[slot].completedMask |= bit;
    Os_RestoreIrq(irq);
}
