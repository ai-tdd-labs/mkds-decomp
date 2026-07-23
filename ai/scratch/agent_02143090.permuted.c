// PURPOSE: Creates a small value from the console's MAC address.
extern void Os_GetMacAddress(unsigned char *address);

unsigned short func_02143090(void)
{
    unsigned char address[6];
    int i;
    unsigned short sum;

    Os_GetMacAddress(address);
    sum = 0;
    for (i = 0; i < 6; i++) {
        sum = (unsigned short)(sum + address[i]);
    }

    sum = (unsigned short)(sum + *(volatile unsigned int *)0x027ffc3c);
    sum = (unsigned short)(sum * 13);
    return (unsigned short)(sum % 10 + 30);
}
