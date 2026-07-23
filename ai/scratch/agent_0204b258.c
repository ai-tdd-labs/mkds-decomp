// PURPOSE: Clears the text terminator when needed and reports whether its CRC is valid.

extern int ComputeCRC_from_thumb(void *buffer, unsigned int length, unsigned int mode);

int func_0204b258(void *buffer, unsigned int length, unsigned int mode)
{
    unsigned char *end = (unsigned char *)buffer + length - 4;

    if (mode == 0) {
        end[0] = 0;
        end[1] = 0;
    }
    if (ComputeCRC_from_thumb(buffer, length, mode) != 0) {
        return 0;
    }
    return 1;
}
