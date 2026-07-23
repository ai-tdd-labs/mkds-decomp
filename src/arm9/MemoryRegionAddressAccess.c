/* PURPOSE: Touches the boundaries of several system memory regions.
 * No arguments. Queries the start and end addresses of regions 0, 3, and 4.
 * The returned addresses are discarded, so these calls probably trigger or
 * verify SDK memory-region access during startup. */

extern void *Os_GetMemoryRegionStartAddress(int region);
extern void *Os_GetMemoryRegionEndAddress(int region);

void MemoryRegionAddressAccess(void) {
    Os_GetMemoryRegionStartAddress(0);
    Os_GetMemoryRegionEndAddress(0);
    Os_GetMemoryRegionStartAddress(3);
    Os_GetMemoryRegionEndAddress(3);
    Os_GetMemoryRegionStartAddress(4);
    Os_GetMemoryRegionEndAddress(4);
}
