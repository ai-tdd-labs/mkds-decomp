// PURPOSE: Prepares the card backup system and resets its shared operation state.
typedef struct CardBackupWork {
    int state;
    int field_04;
    int lockId;
    int active;
    int field_10;
    int field_14;
    unsigned char pad_18[0x10];
    int field_28;
    unsigned char pad_2c[4];
    int field_30;
    unsigned char pad_34[0xc];
    int field_40;
    unsigned char pad_44[4];
    int field_48;
    unsigned char pad_4c[0xc];
    int field_58;
    int field_5c;
} CardBackupWork;

extern CardBackupWork *data_021759d4;

extern int Os_IsEmulator(void);
extern int AllocateLockCardBackupResource_from_thumb(void);
extern int MaybeInitializeBackup(void *argument);
extern void CleanupUnlockBackup_from_thumb(void);

void InitializePrepareBackup_from_thumb(void)
{
    if (*(volatile unsigned short *)0x027ffc40 == 2 || Os_IsEmulator() != 0) {
        data_021759d4->active = 0;
        return;
    }

    data_021759d4->active = 1;
    AllocateLockCardBackupResource_from_thumb();
    MaybeInitializeBackup((void *)0x1202);
    CleanupUnlockBackup_from_thumb();

    data_021759d4->state = 0;
    data_021759d4->field_04 = 0;
    data_021759d4->lockId = -3;
    data_021759d4->field_10 = 0;
    data_021759d4->field_14 = 0;
    data_021759d4->field_28 = 0;
    data_021759d4->field_30 = 0;
    data_021759d4->field_40 = 0;
    data_021759d4->field_48 = 0;
    data_021759d4->field_58 = -1;
    data_021759d4->field_5c = -1;
}
