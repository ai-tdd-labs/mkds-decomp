/* PURPOSE: Resets the working data for one player slot.
 * The slot index selects one entry and one bit in each pending mask.
 * It clears the entry's main data area and probably resets its trailing state.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u8 working_data[0x4C0];
    u8 unknown_4C0[0xC0];
    u32 state_580;
    u32 state_584;
    u16 valid_slot_mask;
    u16 unknown_58A;
    u16 state_58C;
    u8 unknown_58E[2];
} Entry;

typedef struct {
    u16 unknown_0;
    u16 pending_mask_2;
    u16 pending_mask_4;
    u8 unknown_6[0xA];
    Entry entries[1];
} EntryPool;

extern EntryPool *data_0216fc40;
extern void Mem_CpuFill16(u16 value, void *destination, u32 size);

void func_0200895c(int slot)
{
    volatile u16 fill_value;
    u32 slot_bit = 1 << slot;

    data_0216fc40->pending_mask_2 &= ~slot_bit;
    data_0216fc40->pending_mask_4 &= ~slot_bit;

    data_0216fc40->entries[slot].state_580 = 0;
    data_0216fc40->entries[slot].state_584 = 0;
    data_0216fc40->entries[slot].valid_slot_mask = 0;
    data_0216fc40->entries[slot].state_58C = 0;

    fill_value = 0;
    Mem_CpuFill16(fill_value, data_0216fc40->entries[slot].working_data, 0x4C0);
}
