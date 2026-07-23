// PURPOSE: Checks whether save data work is still running.
// The shared holder probably stores its busy flag at byte offset 0x28.
// A clear flag falls through to the save-data I/O manager query.

#pragma optimize_for_size on

extern void *data_0217aa08;
extern int func_020360a0(void);

int func_0203606c(void)
{
    int busy = ((unsigned char *)data_0217aa08)[0x28];

    if (busy != 0)
        return 1;

    return func_020360a0();
}
