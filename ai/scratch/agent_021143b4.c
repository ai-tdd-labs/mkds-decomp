// PURPOSE: Counts online records with the status flag set.
// This function checks the first 60 online record slots.
// It probably returns the stored count when the shared record pointer is ready.
// The slot index is passed to the existing online-record status checker.

#pragma optimize_for_size on

typedef unsigned short u16;

extern u16 *data_0217d34c;
extern int func_02060b34(int slot);

int func_021143b4(void)
{
    int i;
    u16 count = 0;

    if (data_0217d34c == 0) {
        i = count;
        do {
            if (func_02060b34((unsigned char)i) != 0) {
                count++;
            }
            i++;
        } while (i < 0x3c);
        return count;
    }

    return *data_0217d34c;
}
