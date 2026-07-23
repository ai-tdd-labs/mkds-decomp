// PURPOSE: Clears the shared entry pool before it is used.
// The global probably points to all per-player entry records.
// It clears the full allocation and then marks its header as initialized.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct EntryPool {
    u8 padding_00[0xc];
    u16 initialized;
} EntryPool;

extern EntryPool *data_0216fc40;
extern void Mem_CpuFastMemorySet(u32 value, void *dst, u32 size);

void func_020092a4(void)
{
    volatile u32 zero;

    Mem_CpuFastMemorySet(zero = 0, data_0216fc40, 0x5910);
    data_0216fc40->initialized = 1;
}
