/*
 * PURPOSE: Handles the default extra-file operation for the ROM archive.
 * The operation code probably reports support or locks and unlocks the current ROM resource.
 * The archive argument is unused by this default handler.
 */

typedef unsigned short u16;

extern unsigned int data_0216f354;
extern void Card_LockRomResource(u16 resource);
extern void Card_UnlockRomResource(u16 resource);

int Fs_RomArchive_ExtraFileOperationHandler_Default(void *archive, int operation)
{
    // PURPOSE: Handles the default extra-file operation for the ROM archive.
    switch (operation) {
    case 9:
        Card_LockRomResource((u16)data_0216f354);
        return 0;
    case 10:
        Card_UnlockRomResource((u16)data_0216f354);
        return 0;
    case 1:
        return 4;
    }

    return 8;
}
