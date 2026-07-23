// PURPOSE: Gets the result stored for a cup entry.
// Copies the requested cup entry into a temporary record.
// Returns its result byte, or three when the entry has no result.

typedef struct CupEntry {
    unsigned char pad0[0x18];
    unsigned char has_result;
    unsigned char pad19[3];
    unsigned char result;
} CupEntry;

extern void CopyCupEntryTo_from_thumb(int cup, int entry, CupEntry *out);

int CupGetResult(int cup, int entry) {
    CupEntry result;

    CopyCupEntryTo_from_thumb(cup, entry, &result);
    if (result.has_result != 0) {
        return result.result;
    }
    return 3;
}
