// PURPOSE: Checks whether every active global entry has its first flag set.
//
// Reads the probably active-entry count from the global work object.
// It returns one only when bit zero is set in the flag word of every entry.

typedef struct GlobalWork {
    char _00[0x48];
    int count_48;
} GlobalWork;

extern GlobalWork *data_02174e3c;
extern void *GetGlobalCA_from_thumb(void);

int func_0202b888(void)
{
    int result = 1;
    int index = 0;
    int offset;

    if (index < data_02174e3c->count_48) {
        offset = index;
        do {
        /* Each global entry has the tested flag word at +0x14. */
            result &= *(int *)((char *)GetGlobalCA_from_thumb() + offset + 0x14);
            offset += 0x18;
            index++;
        } while (index < data_02174e3c->count_48);
    }
    return result;
}
