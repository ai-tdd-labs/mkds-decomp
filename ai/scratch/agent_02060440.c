// PURPOSE: Checks whether a cup has a saved record.
// Takes the cup and class identifiers used by the save-data helper.
// Copies the probably matching cup entry into a local buffer.
// Returns that entry's record flag.

extern void CopyCupEntryTo_from_thumb(int cup, int cc, void *entry);

int CupHasRecord(int cup, int cc)
{
    volatile unsigned char entry[0x24];

    CopyCupEntryTo_from_thumb(cup, cc, entry);
    {
        unsigned char has_record = entry[0x18];
        return has_record == 0 ? 0 : has_record;
    }
}
