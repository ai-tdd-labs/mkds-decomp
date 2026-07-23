/* PURPOSE: Clears all stored data for one player slot.
 * The slot index selects a bit in two pending masks and one 0x590-byte entry.
 * Both mask bits are cleared before the selected entry is filled with zeroes. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u16 unk0;
    u16 pending2;
    u16 pending4;
    u8 unk6[0xA];
    u8 entries[1][0x590];
} EntryPool;

extern EntryPool *data_0216fc40;
extern void Mem_CpuFill16(u16 value, void *destination, u32 size);

void func_020089d0(int slot)
{
    volatile u16 fill;
    u32 slot_bit = 1 << slot;

    data_0216fc40->pending2 &= ~slot_bit;
    data_0216fc40->pending4 &= ~slot_bit;

    fill = 0;
    Mem_CpuFill16(fill, data_0216fc40->entries[slot], 0x590);
}
