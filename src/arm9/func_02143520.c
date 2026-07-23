/* PURPOSE: Copies received wireless data into a caller-provided buffer.
 * The destination must be non-null and the wireless subsystem must be ready.
 * It invalidates the shared receive buffer before copying its 1,980 bytes.
 * Returns the initialization status, 6 for a null destination, or 0 on success.
 */

typedef unsigned int u32;

typedef struct StructWM {
    void *buffer1;
    void *buffer2;
} StructWM;

extern StructWM *Wm_GetGlobal(void);
extern int Wm_CheckInitialized(void);
extern void DC_InvalidateRangeNoClean(void *start, u32 length);
extern void MIi_CpuCopyFast(const void *source, void *destination, u32 length);

int func_02143520(void *destination)
{
    StructWM *wireless = Wm_GetGlobal();
    int result = Wm_CheckInitialized();

    if (result != 0) {
        return result;
    }
    if (destination == 0) {
        return 6;
    }

    DC_InvalidateRangeNoClean(wireless->buffer2, 0x7bc);
    MIi_CpuCopyFast(wireless->buffer2, destination, 0x7bc);
    return 0;
}
