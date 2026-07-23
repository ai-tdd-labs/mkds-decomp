// PURPOSE: Releases the saved backup resource lock.
// This function has no arguments.
// It probably unlocks the active backup resource and clears its lock ID.

typedef struct UnlockBackupState {
    unsigned char padding_00[8];
    int lockId;
} UnlockBackupState;

extern UnlockBackupState *data_021759d4;

extern void Card_UnlockBackupResource(unsigned short lockId);
extern void Os_ReleaseLockId(unsigned short lockId);

void CleanupUnlockBackup_from_thumb(void)
{
    if (data_021759d4->lockId != -3) {
        Card_UnlockBackupResource((unsigned short)data_021759d4->lockId);
        Os_ReleaseLockId((unsigned short)data_021759d4->lockId);
        data_021759d4->lockId = -3;
    }
}
