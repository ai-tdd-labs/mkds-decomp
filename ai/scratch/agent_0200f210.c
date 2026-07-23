// PURPOSE: Initializes the processor memory region boundaries once.
// It computes and stores the start and end addresses for the active regions.
// Region two is disabled here by setting both boundaries to zero.

typedef unsigned int u32;

extern int data_021701b4;

extern u32 Os_ComputeMemoryRegionEndAddress(int region);
extern void Os_SetMemoryRegionEndAddress(int region, unsigned int addr);
extern u32 Os_ComputeMemoryRegionStartAddress(int region);
extern void Os_SetMemoryRegionStartAddress(int region, unsigned int addr);

void Os_InitializeMemoryRegionAddresses(void)
{
    if (data_021701b4 != 0) {
        return;
    }

    data_021701b4 = 1;

    Os_SetMemoryRegionEndAddress(0, Os_ComputeMemoryRegionEndAddress(0));
    Os_SetMemoryRegionStartAddress(0, Os_ComputeMemoryRegionStartAddress(0));

    Os_SetMemoryRegionStartAddress(2, 0);
    Os_SetMemoryRegionEndAddress(2, 0);

    Os_SetMemoryRegionEndAddress(3, Os_ComputeMemoryRegionEndAddress(3));
    Os_SetMemoryRegionStartAddress(3, Os_ComputeMemoryRegionStartAddress(3));

    Os_SetMemoryRegionEndAddress(4, Os_ComputeMemoryRegionEndAddress(4));
    Os_SetMemoryRegionStartAddress(4, Os_ComputeMemoryRegionStartAddress(4));

    Os_SetMemoryRegionEndAddress(5, Os_ComputeMemoryRegionEndAddress(5));
    Os_SetMemoryRegionStartAddress(5, Os_ComputeMemoryRegionStartAddress(5));

    Os_SetMemoryRegionEndAddress(6, Os_ComputeMemoryRegionEndAddress(6));
    Os_SetMemoryRegionStartAddress(6, Os_ComputeMemoryRegionStartAddress(6));
}
