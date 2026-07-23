// PURPOSE: Generates a small value from the console MAC address.
extern void Os_GetMacAddress(unsigned char *address);
extern unsigned long long MaybeBoundsCheck(int value, int limit);

int func_0200a184(void)
{
    unsigned char address[6];
    int total;
    int index;
    unsigned char *cursor;

    Os_GetMacAddress(address);
    index = 0;
    total = index;
    cursor = address;
    while (index < 6) {
        total += *cursor;
        cursor++;
        index++;
    }
    return (int)(MaybeBoundsCheck(
                     (total + *(volatile int *)0x027ffc3c) * 7, 20) >>
                 32);
}
