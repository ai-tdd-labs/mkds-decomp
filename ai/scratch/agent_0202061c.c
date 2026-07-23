// PURPOSE: Calculates the CRC for friend data.
/*
 * The first argument is probably a friend-data record.
 * The remaining inputs are passed to the CRC implementation.
 * The implementation writes the resulting byte through its second argument.
 */
typedef unsigned char u8;

extern void Friend_ComputeCrcImpl(void *friendData, u8 *crc, void *data, int size);

u8 ComputeFriendCrc(void *friendData, void *data, int size)
{
    u8 crc = 0;

    Friend_ComputeCrcImpl(friendData, &crc, data, size);
    return crc;
}
