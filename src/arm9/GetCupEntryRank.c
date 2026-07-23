// PURPOSE: Gets a cup entry's rank.
// Copies the selected cup entry into local storage.
// Returns its rank when the entry is present, or the default rank otherwise.

extern void CopyCupEntryTo_from_thumb(int cup, int cc, void *entry);

int GetCupEntryRank(int cup, int cc)
{
    unsigned char entry[0x24];

    CopyCupEntryTo_from_thumb(cup, cc, entry);
    return entry[0x18] != 0 ? entry[0x1e] : 9;
}
