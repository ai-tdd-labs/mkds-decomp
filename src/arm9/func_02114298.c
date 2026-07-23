// PURPOSE: Copies a selected record into a cleared destination buffer.
// The selector chooses a 16-bit table entry from the emblem resource state.
// That entry is reduced to a byte, passed to a helper, and 20 bytes are copied out.
// The helper output is probably a temporary record assembled in the local buffer.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct ResourceState {
    void *field_00;
    void *field_04;
} ResourceState;

extern ResourceState *data_0217d34c;
extern int func_020608fc(int slot, void *output);
extern void Mem_CpuFill8(void *destination, u32 value, u32 size);
extern void CopyMemory16(const void *source, void *destination, u32 size);

void func_02114298(int selector, void *destination, u32 size)
{
    u8 record[0x14];

    func_020608fc((u8)((u16 *)data_0217d34c->field_04)[selector], record);
    Mem_CpuFill8(destination, 0, size);
    CopyMemory16(record, destination, 0x14);
}
