/* PURPOSE: Invalidates the cache for a shared data word.
 * The shared pointer probably identifies a small cache-managed record.
 * It invalidates the word at offset four, then returns that word.
 */
extern void *data_02174e00;
extern void DC_InvalidateRangeNoClean(void *address, int size);

void *func_020218bc(void)
{
    DC_InvalidateRangeNoClean((void *)((char *)data_02174e00 + 4), 4);
    return *(void **)((char *)data_02174e00 + 4);
}
