// PURPOSE: Returns the selected cup entry's signed value.
// Copies the requested cup and class entry into a local record.
// Returns its signed byte at offset 0x1d when its flag at 0x18 is set.
// The record layout is probably a cup-selection entry.

extern void CopyCupEntryTo_from_thumb(int cup, int cc, void *entry);

int func_02060390(int cup, int cc)
{
    char entry[0x24];

    CopyCupEntryTo_from_thumb(cup, cc, entry);
    if ((unsigned char)entry[0x18] != 0) {
        return entry[0x1d];
    }
    return -1;
}
