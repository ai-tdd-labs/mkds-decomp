// PURPOSE: Calculates and stores a checksum for a data block.
// The last four bytes of the block hold two timing bytes and the checksum.
// When the third argument is zero, the timing bytes are refreshed first.
// The exact reason for the timing tag is probably save-data validation.

extern int ComputeCRC_from_thumb(void *data, unsigned int size, unsigned int seed);
extern unsigned long long Os_GetTick(void);

void CalculateCRCChecksum_from_thumb(void *data, unsigned int size, unsigned int keepTime)
{
    unsigned char *checksum = (unsigned char *)data + size - 4;
    unsigned char mask = 0xff;
    unsigned int tick;
    int crc;

    if (keepTime == 0) {
        checksum[0] = 0;
        checksum[1] = 0;
    }
    checksum[2] = 0;
    checksum[3] = 0;

    crc = ComputeCRC_from_thumb(data, size, 0);

    if (keepTime == 0) {
        {
            unsigned long long wideTick = Os_GetTick();
            tick = (unsigned int)((wideTick >> 16) & 0xffULL);
        }
        tick = tick & mask;
        checksum[0] = (unsigned char)tick;
        {
            unsigned long long wideTick = Os_GetTick();
            tick = (unsigned int)((wideTick >> 32) & 0xffULL);
        }
        tick = tick & mask;
        checksum[1] = (unsigned char)tick;
    }
    checksum[2] = (unsigned char)(crc >> 8);
    checksum[3] = (unsigned char)crc;
}
