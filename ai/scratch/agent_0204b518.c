// PURPOSE: Starts a backup card stream command when the card is ready.
// Arguments: none.
// It probably uses the shared card work state to prepare a save operation.
// Returns zero when the card or its backup resource is unavailable.

typedef struct CardWork {
    unsigned char padding_00[0x0c];
    void *busy;
    unsigned char padding_10[0x54];
    void *streamData;
} CardWork;

extern CardWork *data_021759d4;

extern int CardIsNotBusy(void);
extern int AllocateLockCardBackupResource_from_thumb(void);
extern void func_0204b574(void);
extern int Card_RequestStreamCommand(void *arg0, void *arg1, int arg2,
                                     void (*arg3)(void), void *arg4,
                                     int arg5, int arg6, int arg7,
                                     void *arg8);

int func_0204b518(void)
{
    int result;

    if (data_021759d4->busy == 0 || CardIsNotBusy() == 0) {
        return 0;
    }

    result = AllocateLockCardBackupResource_from_thumb();
    if (result == 0) {
        return 0;
    }

    Card_RequestStreamCommand((void *)result, data_021759d4->streamData, 1,
                              func_0204b574, 0, 1, 6, 1, 0);
    return 1;
}
