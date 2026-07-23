// PURPOSE: Clears the cartridge transfer state and creates its lock.
// This has no arguments. It resets the common CTRDG state, probably used by
// cartridge transfer routines, then stores the newly allocated lock ID.

extern void CpuSet(const void *src, void *dst, unsigned int mode);
extern unsigned short Os_AllocateLockId(void);
extern char data_0216fe04[];

void CTRDGi_InitCommon_from_thumb(void)
{
    int zero = 0;

    /* CpuSet's fixed-source mode clears the shared state block. */
    CpuSet(&zero, data_0216fe04, 0x05000001);
    *(unsigned short *)(data_0216fe04 + 2) = Os_AllocateLockId();
}
