// PURPOSE: Builds the staff roll sprites for the current frame.
// It resets the sprite count and adds the first credits cell while active.
// The remaining entries are cleared after the completed sprite data is flushed.

typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u32 first;
    u32 second;
} EndingOamRecord;

typedef struct {
    EndingOamRecord entries[128];
    u16 count;
    u16 padding_402;
} EndingOamBuffer;

typedef struct {
    int frame_count;
    void *palette;
    void *characters;
    void *first_cell;
    EndingOamBuffer oam;
} EndingStaffRollObjectData;

extern EndingStaffRollObjectData *data_0217b4ac;

extern int MaybeMakeOamSlot(void *slot, u16 remaining, void *cell, int unused,
                            int *attributes, int unused2, int enabled);
extern void Arm_FlushRange(void *buffer, u32 size);
extern void Mem_DmaFill32(u32 channel, void *destination, u32 value, u32 size);

void func_020d12e0(void)
{
    int attributes[2];
    EndingOamBuffer *oam;
    int i;
    EndingOamRecord *entry;
    void *cell;

    data_0217b4ac->oam.count = 0;

    if (data_0217b4ac->frame_count < 0x21c) {
        oam = &data_0217b4ac->oam;
        i = oam->count;
        cell = data_0217b4ac->first_cell;
        attributes[0] = 0x80000;
        attributes[1] = 0x60000;
        entry = &oam->entries[i];

        oam->count += MaybeMakeOamSlot(
            entry,
            (u16)(0x80 - i),
            cell,
            0,
            attributes,
            0,
            1);

        for (; i < oam->count; i++, entry++) {
            entry->first = (entry->first & ~0xc00) | 0x400;
            entry->second = (entry->second & ~0xc00) | 0x400;
        }
    }

    Arm_FlushRange(data_0217b4ac->oam.entries, 0x400);
    Mem_DmaFill32(
        3,
        &data_0217b4ac->oam.entries[data_0217b4ac->oam.count],
        0xc0,
        (0x80 - data_0217b4ac->oam.count) * 8);
}
