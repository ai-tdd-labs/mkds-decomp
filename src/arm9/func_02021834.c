// PURPOSE: Invalidates the cache for a shared four-byte value.
// The shared pointer is probably updated by another system.
// It invalidates that value's cache line, then returns the current pointer.

typedef unsigned int u32;

extern void *data_02174e00[];
extern void DC_InvalidateRangeNoClean(void *start, u32 length);

void *func_02021834(void)
{
    DC_InvalidateRangeNoClean(*data_02174e00, 4);
    return *(void **)*data_02174e00;
}
