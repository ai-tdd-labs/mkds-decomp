// PURPOSE: Fills a memory region with a 16-bit value.
// Arguments: destination, fill value, and byte count.
// This probably wraps the platform halfword fill routine.

typedef unsigned short u16;
typedef unsigned int u32;

extern void Mem_CpuFill16(u16 value, void *destination, u32 size);

void DoFill16(u16 *destination, int value, int size) {
    u16 volatile fill_value = value; // Preserve the required halfword reload.
    Mem_CpuFill16(fill_value, destination, size);
}
