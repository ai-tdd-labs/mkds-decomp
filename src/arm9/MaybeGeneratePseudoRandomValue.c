// PURPOSE: Generates a small pseudo-random value from the console MAC address.
extern void Os_GetMacAddress(unsigned char *address);

unsigned short MaybeGeneratePseudoRandomValue(void)
{
    unsigned char address[6];
    unsigned short total;
    int index;
    unsigned char *cursor;

    Os_GetMacAddress(address);
    index = 0;
    total = (unsigned short)index;
    cursor = address;
    while (index < 6) {
        total = (unsigned short)(total + *cursor);
        cursor++;
        index++;
    }

    total = (unsigned short)(total + *(volatile unsigned int *)0x027ffc3c);
    total = (unsigned short)(total * 7);
    return (unsigned short)(total % 20 + 200);
}
