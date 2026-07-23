// PURPOSE: Gets the recorded rank for a cup entry.
// Takes the cup and class identifiers used by the cup-record helper.
// Copies the entry into a local buffer, then returns its rank when valid.
// Returns -1 when the entry probably has no saved record.

extern void CopyCupEntryTo_from_thumb(int cup, int cc, void *entry);

int func_020603e8(int cup, int cc)
{
    unsigned char entry[0x24];

    CopyCupEntryTo_from_thumb(cup, cc, entry);
    return entry[0x18] != 0 ? entry[0x1a] : -1;
}
