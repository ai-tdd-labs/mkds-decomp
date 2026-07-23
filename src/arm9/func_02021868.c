// PURPOSE: Reads a cached signed value from a global table.
// The first argument selects a 0x24-byte table row.
// The second argument selects a signed halfword within that row.

extern char *data_02174e00;
extern void DC_InvalidateRangeNoClean(void *address, unsigned int size);

short func_02021868(int row, int index)
{
    int row_offset;

    row_offset = row * 0x24;
    DC_InvalidateRangeNoClean(&((short *)((char *)data_02174e00 + 0x20 + row_offset))[index], 2);
    return ((short *)((char *)data_02174e00 + 0x20 + row_offset))[index];
}
