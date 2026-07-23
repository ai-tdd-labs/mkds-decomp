// PURPOSE: Allocates and locks the card backup resource.
// Arguments: none.
// Stores the allocated lock ID in the probably shared card work state.
// Returns whether the allocation succeeded and the backup resource was locked.

typedef struct CardBackupWork {
    unsigned char padding_00[8];
    int lockId;
} CardBackupWork;

extern CardBackupWork *data_021759d4;

extern int Os_AllocateLockId(void);
extern void Card_LockBackupResource(unsigned short lockId);

int AllocateLockCardBackupResource_from_thumb(void)
{
    data_021759d4->lockId = Os_AllocateLockId();
    if (data_021759d4->lockId == -3) {
        return 0;
    }
    Card_LockBackupResource((unsigned short)data_021759d4->lockId);
    return 1;
}
