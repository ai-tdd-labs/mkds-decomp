// PURPOSE: Computes the profile ID and its masked friend checksum.
// The inputs probably form the eight-byte profile data.
// A temporary lookup table is built, then the checksum is calculated and
// returned beside the original profile ID as a 64-bit result.

typedef unsigned char u8;

extern void GenerateFriendCrcLookupTable(unsigned int *table, int polynomial);
extern u8 ComputeFriendCrc(void *friendData, void *data, int size);

unsigned long long VerifyChecksumGetProfileId_from_thumb(unsigned int profileId,
                                                         unsigned int checksum)
{
    unsigned int data[2];
    unsigned int lookupTable[64];

    data[0] = profileId;
    data[1] = checksum;
    GenerateFriendCrcLookupTable(lookupTable, 7);
    unsigned long long result;
    result = (unsigned long long)(ComputeFriendCrc(lookupTable, data, 8) & 0x7F) << 32;
    result |= profileId;
    return result;

}
