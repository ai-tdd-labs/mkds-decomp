// PURPOSE: Initializes the memory controller for game startup.
// Sets the WRAM mode, then stops active DMA channels.

extern void Mem_SetWramcnt(int mode);
extern void Mem_DmaStop(int channel);

void Mem_Initialize(void)
{
    Mem_SetWramcnt(3);
    Mem_DmaStop(0);
}
