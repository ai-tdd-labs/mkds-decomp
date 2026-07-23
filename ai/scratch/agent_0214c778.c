// PURPOSE: Rejects DMA0 transfers that use forbidden memory regions.
// Arguments: The enable state, source address, transfer size, and DMA control bits.
// Behavior: Stops the system when either end of a disabled DMA0 transfer is invalid.

typedef unsigned int u32;

extern void Os_Terminate(void);

void MIi_CheckDma0SourceAddress(int enabled, u32 source, u32 size, u32 control)
{
    u32 sourceRegion;

    if (enabled != 0)
    {
        return;
    }

    sourceRegion = source & 0xFF000000;

    if (control != 0)
    {
        if (control == 0x00800000)
        {
            source -= size;
        }
    }
    else
    {
        source += size;
    }

    if (sourceRegion == 0x04000000 || sourceRegion >= 0x08000000)
    {
        Os_Terminate();
        return;
    }

    sourceRegion = source & 0xFF000000;
    if (sourceRegion == 0x04000000 || sourceRegion >= 0x08000000)
    {
        Os_Terminate();
    }
}
