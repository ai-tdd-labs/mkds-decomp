// PURPOSE: Checks whether a cup entry has a record value.
// Takes the cup and class indices used by the save-data helper.
// Copies the probably matching entry into a local buffer.
// Returns its record value, or -1 when no record exists.

extern void CopyCupEntryTo_from_thumb(int entryIndex, int cupIndex,
                                      void *cupEntry);

int func_02060414(int entryIndex, int cupIndex)
{
    unsigned char entry[0x24];

    CopyCupEntryTo_from_thumb(entryIndex, cupIndex, entry);
    if (entry[0x18] != 0) {
        return entry[0x19];
    }
    return -1;
}
