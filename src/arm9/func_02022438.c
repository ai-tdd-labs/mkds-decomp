// PURPOSE: Clears and initializes a small state block.
// The argument is probably a state record with a 0x18-byte area after its header.
// It clears that area, then sets two header fields to the initial limit.

typedef unsigned int u32;
typedef unsigned short u16;

extern void Mem_CpuFill16(u16 value, void *destination, u32 size);

void func_02022438(void *state)
{
    volatile u16 fill_value;

    fill_value = 0; /* Preserve the required halfword stack reload. */
    Mem_CpuFill16(fill_value, (char *)state + 4, 0x18);
    *(u32 *)((char *)state + 4) = 0x1000;
    *(u32 *)((char *)state + 8) = 0x1000;
}
