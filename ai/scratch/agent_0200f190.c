/*
 * PURPOSE: Sets up the main extra memory region addresses.
 * It initializes region two from the system's computed boundaries.
 * The protection setup probably runs unless an existing region is valid.
 */

typedef unsigned int u32;

extern int data_021701b8;

extern u32 Os_ComputeMemoryRegionEndAddress(int region);
extern void Os_SetMemoryRegionEndAddress(int region, unsigned int addr);
extern u32 Os_ComputeMemoryRegionStartAddress(int region);
extern void Os_SetMemoryRegionStartAddress(int region, unsigned int addr);
extern u32 Os_GetSystemFlags(void);
extern void Os_SetSystemRomPU(void *address);
extern void Os_SetVectorBasePU(void *address);

void Os_InitializeMainExMemoryRegionAddress(void)
{
    Os_SetMemoryRegionEndAddress(2, Os_ComputeMemoryRegionEndAddress(2));
    Os_SetMemoryRegionStartAddress(2, Os_ComputeMemoryRegionStartAddress(2));

    if (data_021701b8 != 0) {
        if ((Os_GetSystemFlags() & 3) != 1) {
            return;
        }
    }

    Os_SetSystemRomPU((void *)0x0200002b);
    Os_SetVectorBasePU((void *)0x023e0021);
}
