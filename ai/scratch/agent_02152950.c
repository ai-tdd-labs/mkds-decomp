// PURPOSE: Verifies a friend record against its masked checksum.
typedef unsigned char u8;

extern void GenerateFriendCrcLookupTable(unsigned int *table, int polynomial);
extern u8 ComputeFriendCrc(void *friendData, void *data, int size);

int Friend_VerifyChecksum_from_thumb(unsigned int friendId, unsigned int checksum,
                                     unsigned int friendData)
{
    unsigned int data[2];
    unsigned int lookupTable[64];

    data[0] = friendId;
    data[1] = friendData;
    GenerateFriendCrcLookupTable(lookupTable, 7);

    return (long long)(ComputeFriendCrc(lookupTable, data, 8) & 0x7F) ==
           (unsigned long long)checksum;
}
