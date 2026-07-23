// PURPOSE: Returns the current save operation result while saving is busy.
// Takes no arguments.
// Probably exposes the active save operation's status value, or zero when idle.

typedef struct SaveDataHolder {
    unsigned char pad_00[0x10];
    int status;
} SaveDataHolder;

extern SaveDataHolder *data_021759d4;
extern int SaveDataIoManager_IsBusy(void);

int func_020360a0(void)
{
    return SaveDataIoManager_IsBusy() != 0 ? data_021759d4->status : 0;
}
