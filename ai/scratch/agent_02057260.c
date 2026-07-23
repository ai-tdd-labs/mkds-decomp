// PURPOSE: Clears the saved ghost replay data.
// The global save-data work object probably holds two ghost buffers.
// Both buffers are cleared with their fixed storage sizes.

typedef unsigned int u32;

typedef struct SaveDataGhostWork {
    unsigned char _00[0x14];
    void *ghost_data_a;
    void *ghost_data_b;
} SaveDataGhostWork;

extern SaveDataGhostWork *data_0217aa08;
extern void Mem_CpuFill8(void *dst, int value, u32 size);

void ClearSaveDataGhosts_from_thumb(void)
{
    Mem_CpuFill8(data_0217aa08->ghost_data_a, 0, 0xE00);
    Mem_CpuFill8(data_0217aa08->ghost_data_b, 0, 0x1000);
}
