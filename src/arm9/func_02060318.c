// PURPOSE: Copies a valid cup entry into the caller's output buffer.
// The first two arguments probably select the requested cup entry.
// The helper writes a temporary 32-byte record whose validity byte is checked.
// On success, the first four bytes are copied to the output and one is returned.

typedef unsigned char u8;

extern void CopyCupEntryTo_from_thumb(int cupId, int entryId, u8 *entry);
extern void Mem_CpuCopy8(const void *source, void *destination, unsigned int size);

int func_02060318(int cupId, int entryId, void *output)
{
    u8 entry[0x20];

    CopyCupEntryTo_from_thumb(cupId, entryId, entry);
    if (entry[0x18] == 0)
        return 0;

    Mem_CpuCopy8(entry, output, 4); // Return the entry's leading value.
    return 1;
}
